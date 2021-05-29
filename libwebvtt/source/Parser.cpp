#include "Parser.h"

#include <utf8.h>

#include <chrono>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <string_view>
#include <thread>
#include "Logger.h"

using namespace CPlusPlusLogging;
using namespace std::chrono_literals;

namespace WebVTT
{

    /**
 * @author
 * @date 
 * @param 
 * @return
 */

    Parser::Parser(std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> inputStream) : inputStream(inputStream)
    {
        preprocessedStream = std::make_shared<SyncBuffer<std::u32string, uint32_t>>();
        parserLogger.updateLogType(LogType::CONSOLE);
    };

    Parser::~Parser()
    {
        if (not parsingThread)
            return;
        preProcsessingThread.get()->join();
        parsingThread.get()->join();
    };

    void Parser::cleanDecodedData(std::u32string &input)
    {
        if (input.size() == 0)
            return;

        uint32_t firstC = input.front();
        if (lastReadCR && firstC == LF_C)
        {
            input.erase(input.begin());
            lastReadCR = false;
        }
        if (input.back() == CR_C)
        {
            lastReadCR = true;
        }

        auto end = input.end();
        for (auto current = input.begin(); current != end;)
        {
            uint32_t current_c = *current;
            bool haveNext = (++current) != end;
            uint32_t next_c = haveNext ? *current : 0;
            current--;

            if (current_c == NULL_C)
            {
                *current = REPLACEMENT_C;
            }
            if (current_c == CR_C)
            {
                *current = LF_C;
            }

            if (current_c == CR_C && haveNext && next_c == LF_C)
            {
                auto temp = current++;
                current++;
                input.erase(temp);
            }
            else
                current++;
        }
    }

    void Parser::preProcessDecodedStreamLoop()
    {
        std::string buffer;
        std::u32string decodedData;
        while (true)
        {
            decodedData = inputStream.get()->readMultiple(DEFAULT_READ_NUMBER);

            if (decodedData.length() == 0)
            {
                break;
            }
            cleanDecodedData(decodedData);

            preprocessedStream.get()->writeMultiple(decodedData);
        }
        preprocessedStream.get()->setInputEnded();
    };

    bool Parser::checkIfStringContainsArrow(std::u32string input)
    {
        //TO do - maybe change to string and use regex
        if (input.size() < 3)
            return false;
        auto current = input.begin();
        auto end = input.end();
        do
        {
            auto first = current++;
            auto second = current++;
            auto thrid = current++;
            if (*thrid != HYPEN_GREATHER)
            {
                if (end - current < 3)
                    break;
                continue;
            }
            if (*second != HYPEN_GREATHER)
            {
                if (end - current < 2)
                    break;
                current = thrid;
                continue;
            }
            if (*first != HYPEN_GREATHER)
            {
                if (end - current < 1)
                {
                    break;
                }
                current = second;
            }
            return true;
        } while (true);
        return false;
    };

    std::u32string Parser::collectWebVTTBlock(bool inHeader)
    {
        //[Collect WebVTT Block] Step 1-10
        uint32_t lineCount = 0;
        std::u32string line;
        std::u32string buffer;
        bool seenEOF = false, seenArrow = false;
        //Cue, stylesheet, region = null;

        //[Collect WebVTT Block] Step 11
        while (true)
        {
            //[Collect WebVTT Block][Loop] Step 1
            auto readData = preprocessedStream.get()->readUntilSpecificData(LF_C);
            if (readData.size() != 0)
                line = readData;

            //[Collect WebVTT Block][Loop] Step 2
            lineCount++;

            //Proveriti zbog positiona jos jednom
            //[Collect WebVTT Block][Loop] Step 3
            if (preprocessedStream.get()->isReadDoneAndAdvancedIfNot())
                seenEOF = true;

            //[Collect WebVTT Block][Loop] Step 4
            bool lineContainArrow = checkIfStringContainsArrow(line);
            if (lineContainArrow)
            {
                //[Collect WebVTT Block][Loop][Line Contain Arrow] Step 1
                if (not inHeader and (lineCount == 1 or lineCount == 2 and not seenArrow))
                {
                    //[Collect WebVTT Block][Loop][Line Contain Arrow] [Cue] Steps [1-4]
                    seenArrow = true;
                    //Cue creation
                    //Collect cue info from line
                }
                else
                {
                    //position = previous position;
                }
            }
            else
            {
                if (not inHeader and lineCount == 2)
                {
                }
            }
            if (seenEOF)
                break;
        }
        return buffer;
    }

    bool Parser::startParsing()
    {
        if (parsingStarted)
            return false;
        preProcsessingThread = std::make_unique<std::thread>(&Parser::preProcessDecodedStreamLoop, this);
        parsingThread = std::make_unique<std::thread>(&Parser::parsingLoop, this);
        return true;
    }

    void Parser::parsingLoop()
    {
        uint32_t position = 0;
        bool seenCue = false;
        bool fileIsOK = true;
        //just try
        std::u32string readData;
        std::optional<uint32_t> readOneDataOptional;
        std::u32string EXTENSION_NAME = utf8::utf8to32(std::string_view("WEBVTT"));
        constexpr int EXTENSION_NAME_LENGTH = 6;

        while (true)
        {
            //[Main loop] Steps [2-6]
            auto readData = preprocessedStream.get()->readMultiple(EXTENSION_NAME_LENGTH);
            if (readData != EXTENSION_NAME)
            {
                fileIsOK = false;
                break;
            }

            readOneDataOptional = preprocessedStream.get()->isReadDoneAndAdvancedIfNot();
            if (!readOneDataOptional.has_value())
            {
                break;
            }

            //[Main loop] Step 6
            uint32_t readOne = readOneDataOptional.value();
            if (readOne != SPACE_C && readOne != LF_C && readOne != TAB_C)
            {
                fileIsOK = false;
                break;
            }

            //[Main loop] Step 7
            preprocessedStream.get()->readUntilSpecificData(LF_C);

            //[Main loop] Step 8
            readOneDataOptional = preprocessedStream.get()->isReadDoneAndAdvancedIfNot();
            if (!readOneDataOptional.has_value())
            {
                break;
            }

            //[Main loop] Step 9
            readOneDataOptional = preprocessedStream.get()->isReadDoneAndAdvancedIfNot();

            //[Main loop] Step 10
            if (!readOneDataOptional.has_value())
            {
                break;
            }

            //[Main loop] Step 11
            if (readOneDataOptional.value() != LF_C)
            {
                //Collect Header
            }
            else
            {
                readOneDataOptional = preprocessedStream.get()->readNext();
            }

            //[Main loop] Step 12
            preprocessedStream.get()->readUntilSpecificData(LF_C);

            //[Main loop] Step 13
            //List<Region> regions = new List<>();

            //[Main loop] Step 14
            //Maybe to extract to seperate function...
            while (readOneDataOptional.has_value())
            {
                //[Block loop] Step1
                //WebVTT::Block blosk =  CollectWebVTTBlock();

                //[Block loop] Steps [2-4]
                //Based of block tipe add it to specific output
                //list of cues, stylesheets or region object

                //[Block loop] Step 5
                preprocessedStream.get()->readUntilSpecificData(LF_C);
                readOneDataOptional = preprocessedStream.get()->isReadDoneAndAdvancedIfNot();
            }
            break;
        }
        if (!fileIsOK)
        {
            parserLogger.error("Eror while parsing!\n");
        }
        else
        {
            parserLogger.info("Parsing sucessful!\n");
        }
        std::cout << std::flush;
    }

}