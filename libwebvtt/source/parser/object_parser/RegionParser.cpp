#include "exceptions/parser_util/IteratorsNotPointToGivenString.hpp"
#include "exceptions/parser_util/PercentageFormatNotValid.hpp"
#include "parser/object_parser/RegionParser.hpp"
#include "parser/ParserUtil.hpp"
#include "logger/LoggingUtility.hpp"
#include "exceptions/parser_util/ParsingCoordinatesError.hpp"
#include "exceptions/parser_util/ParsingFloatPointNumber.hpp"
#include "exceptions/parser_util/ParsingLongNumberError.hpp"

namespace webvtt {

void RegionParser::buildObjectFromString(std::u32string_view input) {
  std::u32string_view setting;
  auto position = input.begin();
  std::u32string characters = {ParserUtil::SPACE_C, ParserUtil::TAB_C, ParserUtil::LF_C, ParserUtil::CR_C};

  try {
    while (position != input.end()) {
      setting = ParserUtil::parseUntilAnyOfGivenCharacters(input, characters, position);
      if (position != input.end())
        position++;
      auto settingInfoOptional = ParserUtil::splitStringAroundCharacter(setting, ParserUtil::COLON_C);

      if (!settingInfoOptional.has_value())
        continue;

      DILOGI(utf8::utf32to8(setting));

      auto[settingName, settingValue] = settingInfoOptional.value();

      if (ParserUtil::compareU32Strings(settingName, ID_SETTING)) {
        parseAndSetIdSetting(settingValue);
        continue;
      }
      if (ParserUtil::compareU32Strings(settingName, WIDTH_SETTING)) {
        parseAndSetWidthSetting(settingValue);
        continue;
      }
      if (ParserUtil::compareU32Strings(settingName, LINES_SETTING)) {
        parseAndSetLinesSetting(settingValue);
        continue;
      }
      if (ParserUtil::compareU32Strings(settingName, REGION_ANCHOR_SETTING)) {
        parseAndSetAnchorSetting(settingValue);
        continue;
      }
      if (ParserUtil::compareU32Strings(settingName, VIEW_PORT_ANCHOR_SETTING)) {
        parseAndSetViewPortAnchorSetting(settingValue);
        continue;
      }
      if (ParserUtil::compareU32Strings(settingName, SCROLL_SETTING)) {
        parseAndSetScrollSetting(settingValue);
        continue;
      }
      if (position != input.end())
        position++;
    }
  } catch (const IteratorsNotPointToGivenString &error) {
    DILOGE(error.what());
  }
}

void RegionParser::parseAndSetIdSetting(std::u32string_view settingValue) {
  currentObject->setIdentifier(settingValue);
}

void RegionParser::parseAndSetWidthSetting(std::u32string_view settingValue) {
  try {
    double value = ParserUtil::parsePercentage(settingValue);

    currentObject->setWidth(value);
  }
  catch (const PercentageFormatNotValid &error) {
    DILOGE(error.what());
  }
}

void RegionParser::parseAndSetLinesSetting(std::u32string_view settingValue) {
  try {
    double value = ParserUtil::parseLongNumber(settingValue, 10);

    currentObject->setLines(value);
  }
  catch (const ParsingLongNumberError &error) {
    DILOGE(error.what());
  }
}

void RegionParser::parseAndSetAnchorSetting(std::u32string_view settingValue) {
  try {
    auto[xCoord, yCoord] = ParserUtil::parseCoordinates(settingValue, ParserUtil::COMMA_C);

    currentObject->setAnchor({xCoord, yCoord});
  }
  catch (const ParsingCoordinatesError &error) {
    DILOGE(error.what());
  }
}

void RegionParser::parseAndSetViewPortAnchorSetting(std::u32string_view settingValue) {
  try {
    auto[xCoord, yCoord] = ParserUtil::parseCoordinates(settingValue, ParserUtil::COMMA_C);
    currentObject->setViewAnchorPort({xCoord, yCoord});
  }
  catch (const ParsingCoordinatesError &error) {
    DILOGE(error.what());
  }
}

void RegionParser::parseAndSetScrollSetting(std::u32string_view settingValue) {
  if (ParserUtil::compareU32Strings(settingValue, U"up")) {
    currentObject->setScrollValue(Region::ScrollType::UP);
  }
}
}