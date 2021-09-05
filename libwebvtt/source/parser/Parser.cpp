#include "parser/Parser.hpp"
#include "elements/webvtt_objects/Block.hpp"
#include "elements/webvtt_objects/Cue.hpp"
#include "parser/ParserUtil.hpp"
#include "logger/LoggingUtility.hpp"
#include "exceptions/FileFormatError.hpp"
#include <iostream>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <thread>
#include <utility>

namespace webvtt {

const std::shared_ptr<UniquePtrSyncBuffer<Cue>> Parser::getCueBuffer() {
  return cues;
}
const std::shared_ptr<UniquePtrSyncBuffer<Region>> Parser::getRegionBuffer() {
  return regions;
}
const std::shared_ptr<UniquePtrSyncBuffer<StyleSheet>> Parser::getStyleSheetBuffer() {
  return styleSheets;
}

Parser::Parser(std::shared_ptr<StringSyncBuffer<std::u32string, uint32_t>> inputStream) : inputStream(std::move(
    inputStream)) {
  preprocessedStream = std::make_unique<StringSyncBuffer<std::u32string, uint32_t>>();

  cueParser = std::make_unique<CueParser>(regions);
  styleSheetParser = std::make_unique<StyleSheetParser>();
  regionParser = std::make_unique<RegionParser>();

  cues = std::make_shared<UniquePtrSyncBuffer<Cue>>();
  regions = std::make_shared<UniquePtrSyncBuffer<Region>>();
  styleSheets = std::make_shared<UniquePtrSyncBuffer<StyleSheet>>();

};

Parser::~Parser() {
  if (not parsingThread)
    return;
  preProcessingThread->join();
  parsingThread->join();
  DILOGE("end of parsing");
};

void Parser::cleanDecodedData(std::u32string &input) {
  if (input.empty())
    return;

  uint32_t firstC = input.front();
  if (lastReadCR && firstC == ParserUtil::LF_C) {
    input.erase(input.begin());
    lastReadCR = false;
  }
  if (input.back() == ParserUtil::LF_C) {
    lastReadCR = true;
  }

  for (auto current = input.begin(); current != input.end();) {
    uint32_t current_c = *current;
    bool haveNext = std::next(current) != input.end();
    uint32_t next_c = haveNext ? *current : 0;

    if (current_c == ParserUtil::NULL_C || current_c == ParserUtil::FFFF_C) {
      *current = ParserUtil::REPLACEMENT_C;
    }
    if (current_c == ParserUtil::CR_C) {
      *current = ParserUtil::LF_C;
    }

    if (current_c == ParserUtil::CR_C && haveNext && next_c == ParserUtil::LF_C) {
      current = input.erase(current);
    } else
      std::advance(current, 1);
  }
}

void Parser::preProcessDecodedStreamLoop() {
  std::string buffer;
  std::u32string decodedData;
  try {
    while (true) {
      decodedData = inputStream->readMultiple(DEFAULT_READ_NUMBER);

      if (decodedData.length() == 0) {
        break;
      }
      cleanDecodedData(decodedData);

      preprocessedStream->writeMultiple(decodedData);
    };
    preprocessedStream->setInputEnded();
    inputStream->clearBufferUntilReadPosition();
  }
  catch (const std::bad_alloc &error) {
    preprocessedStream->setInputEnded();
    DILOGE(error.what());
    return;
  }
};

bool Parser::collectBlock(bool inHeader) {

  uint32_t lineCount = 0;
  auto previousPosition = preprocessedStream->getReadPosition();
  std::u32string line, buffer;
  bool seenEOF = false, seenArrow = false;
  bool isNewCue = false, isNewRegion = false, isNewStyleSheet = false;

  while (true) {
    auto readData = preprocessedStream->readUntilSpecificData(ParserUtil::LF_C);
    line = readData;

    lineCount++;

    auto readOneDataOptional = preprocessedStream->readNext();
    if (!readOneDataOptional.has_value())
      seenEOF = true;
    else {
      readOneDataOptional = preprocessedStream->peekOne();
    }

    bool lineContainArrow = ParserUtil::stringContainsSeparator(line, ParserUtil::TIME_STAMP_SEPARATOR);
    if (lineContainArrow) {

      if (!inHeader && (lineCount == 1 || (lineCount == 2 && !seenArrow))) {
        seenArrow = true;

        preprocessedStream->clearBufferUntilReadPosition();
        previousPosition = preprocessedStream->getReadPosition();

        DILOGI("FOUND CUE");
        isNewCue = true;

        auto position = std::u32string_view(line).begin();
        bool success = cueParser->setNewObjectForParsing(std::make_unique<Cue>(buffer));
        success = cueParser->parseTimingAndSettings(line, position);

        if (!success) {
          DILOGE("Cue timing an settings not parsed successfully");
        }
        buffer.clear();
        seenCue = true;
      } else {
        preprocessedStream->setReadPosition(previousPosition);
        break;
      }
    } else if (line.length() == 0)
      break;
    else {
      if (!inHeader and lineCount == 2) {
        std::u32string_view temp = buffer;
        ParserUtil::strip(temp, ParserUtil::isASCIIWhiteSpaceCharacter);
        auto tempStyleSheet = temp.substr(0, STYLE_NAME.length());
        auto tempRegion = temp.substr(0, REGION_NAME.length());
        if (!seenCue && tempStyleSheet == STYLE_NAME) {

          DILOGI("FOUND  STYLESHEET");
          isNewStyleSheet = true;
          buffer.clear();
        } else if (!seenCue && tempRegion == REGION_NAME) {

          DILOGI("FOUND REGION");
          isNewRegion = true;
          regionParser->setNewObjectForParsing(std::make_unique<Region>());
          buffer.clear();
        }
      }

      if (!buffer.empty())
        buffer.push_back(ParserUtil::LF_C);
      buffer.append(line);

      previousPosition = preprocessedStream->getReadPosition();
    }
    if (seenEOF)
      break;
  }

  if (isNewCue) {
    cueParser->setTextToObject(buffer);
    cueParser->parseTextStyleAndMakeStyleTree(predefinedLanguage);
    cues->writeNext(cueParser->collectCurrentObject());
    return true;
  }
  if (isNewStyleSheet) {
    styleSheetParser->parseCSSRules(buffer);
    styleSheets->writeMultiple(styleSheetParser->getStyleSheets());

    return true;
  }

  if (isNewRegion) {
    regionParser->parseSettings(buffer);
    regions->writeNext(regionParser->collectCurrentObject());
    return true;
  }

  return false;
}

bool Parser::startParsing() {
  if (parsingStarted)
    return false;
  parsingStarted = true;
  preProcessingThread = std::make_unique<std::thread>(&Parser::preProcessDecodedStreamLoop, this);
  parsingThread = std::make_unique<std::thread>(&Parser::parsingLoop, this);
  return true;
}

void Parser::parsingLoop() {
  try {

    std::u32string readData;
    std::optional<uint32_t> readOneDataOptional;

    //Read webvtt at the beginning of file
    readData = preprocessedStream->readMultiple(EXTENSION_NAME_LENGTH);
    if (readData != EXTENSION_NAME) {
      DILOGE("File need to start witg WEBVTT");
      throw FileFormatError();
    }

    readOneDataOptional = preprocessedStream->isReadDoneAndAdvancedIfNot();
    if (!readOneDataOptional.has_value()) {
      DILOGE("Need additonal character after WEBVTT");
      throw FileFormatError();
    }

    uint32_t readOne = readOneDataOptional.value();
    if (readOne != ParserUtil::SPACE_C && readOne != ParserUtil::LF_C && readOne != ParserUtil::TAB_C) {
      DILOGE("Need additonal character after WEBVTT(Space, line feed or tab");
      throw FileFormatError();
    }

    preprocessedStream->readUntilSpecificData(ParserUtil::LF_C);

    readOneDataOptional = preprocessedStream->isReadDoneAndAdvancedIfNot();
    if (!readOneDataOptional.has_value()) {
      DILOGI("Parsing done but no useful data");
      return;
    }

    readOneDataOptional = preprocessedStream->peekOne();
    if (!readOneDataOptional.has_value()) {
      DILOGI("Parsing done but no useful data");
      return;
    }

    if (readOneDataOptional.value() != ParserUtil::LF_C) {
      DILOGI("Collecting block in header");
      collectBlock(true);
    } else {
      readOneDataOptional = preprocessedStream->readNext();
    }

    preprocessedStream->readWhileSpecificData(ParserUtil::LF_C);

    while ((readOneDataOptional = preprocessedStream->peekOne()).has_value()) {
      DILOGI("Collecting block not in header");
      collectBlock(false);
      //Collected block was put in list inside the function

      preprocessedStream->readWhileSpecificData(ParserUtil::LF_C);
    }
  }
  catch (const FileFormatError &error) {
    DILOGE(error.what());
    return;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    return;
  }
}

void Parser::setPredefineLanguage(std::u32string_view language) {
  this->predefinedLanguage = language;
}
} // namespace webvtt