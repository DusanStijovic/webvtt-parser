#ifndef WEBVTT_PARSER_H
#define WEBVTT_PARSER_H

#include "utf8.h"
#include "buffer/StringSyncBuffer.h"
#include "buffer/UniquePtrSyncBuffer.h"
#include "logger/Logger.h"
#include "elements/webvtt_objects/Cue.h"
#include "elements/webvtt_objects/Region.h"
#include "elements/webvtt_objects/StyleSheet.h"
#include "parser/CueParser.h"
#include "parser/StyleSheetParser.h"
#include "parser/RegionParser.h"
#include <string>
#include <array>
#include <list>
#include <memory.h>
#include <thread>

namespace WebVTT
{

  class Parser
  {

  public:
    explicit Parser(std::shared_ptr<StringSyncBuffer<std::u32string, uint32_t>> inputStream);
    void setPredefineLanguage(std::u32string_view language);
    bool startParsing();

    const std::shared_ptr<UniquePtrSyncBuffer<Region>> getRegionBuffer();
    const std::shared_ptr<UniquePtrSyncBuffer<Cue>> getCueBuffer();
    const std::shared_ptr<UniquePtrSyncBuffer<StyleSheet>> getStyleSheetBuffer();

    ~Parser();

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
}

#endif