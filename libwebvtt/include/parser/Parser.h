#ifndef WEBVTT_PARSER_H
#define WEBVTT_PARSER_H

#include "SyncBuffer.h"
#include "Logger.h"
#include "utf8.h"
#include "Cue.h"
#include "Region.h"
#include "StyleSheet.h"
#include "CueParser.h"
#include "StyleSheetParser.h"
#include "RegionParser.h"
#include <string>
#include <array>
#include <list>
#include <memory.h>
#include <thread>
#include <Block.h>

namespace WebVTT {

    using namespace CPlusPlusLogging;

    class Parser {

    public:
        explicit Parser(std::shared_ptr<SyncBuffer < std::u32string, uint32_t>>

        inputStream);

        bool startParsing();

        ~Parser();

    private:
        constexpr static std::u32string_view EXTENSION_NAME = U"WEBVTT";
        constexpr static std::u32string_view STYLE_NAME = U"STYLE";
        constexpr static std::u32string_view REGION_NAME = U"REGION";

        constexpr static int EXTENSION_NAME_LENGTH = 6;
        constexpr static int DEFAULT_READ_NUMBER = 15;

        bool lastReadCR = false;
        bool seenCue = false;

        bool parsingStarted = false;

        std::shared_ptr<SyncBuffer < std::u32string, uint32_t>> inputStream;
        std::shared_ptr<SyncBuffer < std::u32string, uint32_t>> preprocessedStream;

        std::unique_ptr<std::thread> preProcessingThread;
        std::unique_ptr<std::thread> parsingThread;

        std::unique_ptr<CueParser> cueParser;
        std::unique_ptr<StyleSheetParser> styleSheetParser;
        std::unique_ptr<RegionParser> regionParser;


        std::list<std::shared_ptr<Cue>> cues;
        std::list<std::shared_ptr<Region>> regions;
        std::list<std::shared_ptr<StyleSheet>> styleSheets;



        Logger parserLogger{"parserLog.txt"};

        //Preprocessing
        void cleanDecodedData(std::u32string &input);

        void preProcessDecodedStreamLoop();

        //Parsing
        void parsingLoop();

        bool collectBlock(bool inHeader);
    };
}

#endif