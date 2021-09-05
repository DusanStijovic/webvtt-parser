#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_PARSER_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_PARSER_HPP_

#include "utf8.h"
#include "buffer/StringSyncBuffer.hpp"
#include "buffer/UniquePtrSyncBuffer.hpp"
#include "elements/webvtt_objects/Cue.hpp"
#include "elements/webvtt_objects/Region.hpp"
#include "elements/webvtt_objects/CueStyleSheet.hpp"
#include "elements/webvtt_objects/RegionStyleSheet.hpp"
#include "parser/object_parser/CueParser.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/object_parser/RegionParser.hpp"
#include <string>
#include <array>
#include <list>
#include <memory.h>
#include <thread>

namespace webvtt {

class Parser {

 public:
  explicit Parser(std::shared_ptr<StringSyncBuffer<std::u32string, uint32_t>> inputStream);
  void setPredefineLanguage(std::u32string_view language);
  bool startParsing();

  const std::shared_ptr<UniquePtrSyncBuffer<Region>> getRegionBuffer();
  const std::shared_ptr<UniquePtrSyncBuffer<Cue>> getCueBuffer();
  const std::shared_ptr<UniquePtrSyncBuffer<StyleSheet>> getStyleSheetBuffer();

  Parser() = default;
  Parser(const Parser &) = delete;
  Parser(Parser &&) = delete;
  Parser &operator=(const Parser &) = delete;
  Parser &operator=(Parser &&) = delete;
  virtual ~Parser();

 private:
  constexpr static std::u32string_view EXTENSION_NAME = U"WEBVTT";
  constexpr static std::u32string_view STYLE_NAME = U"STYLE";
  constexpr static std::u32string_view REGION_NAME = U"REGION";

  std::u32string predefinedLanguage;

  constexpr static int EXTENSION_NAME_LENGTH = 6;
  constexpr static int DEFAULT_READ_NUMBER = 15;

  bool lastReadCR = false;
  bool seenCue = false;

  bool parsingStarted = false;

  std::shared_ptr<StringSyncBuffer<std::u32string, uint32_t>> inputStream;
  std::unique_ptr<StringSyncBuffer<std::u32string, uint32_t>> preprocessedStream;

  std::unique_ptr<std::thread> preProcessingThread;
  std::unique_ptr<std::thread> parsingThread;

  std::unique_ptr<CueParser> cueParser;
  std::unique_ptr<StyleSheetParser> styleSheetParser;
  std::unique_ptr<RegionParser> regionParser;

  std::shared_ptr<UniquePtrSyncBuffer<Cue>> cues;
  std::shared_ptr<UniquePtrSyncBuffer<Region>> regions;
  std::shared_ptr<UniquePtrSyncBuffer<StyleSheet>> styleSheets;

  void cleanDecodedData(std::u32string &input);

  void preProcessDecodedStreamLoop();

  void parsingLoop();

  bool collectBlock(bool inHeader);
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_PARSER_HPP_