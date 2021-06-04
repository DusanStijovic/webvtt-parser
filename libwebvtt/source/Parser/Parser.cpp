#include <iostream>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <thread>
#include <Block.h>
#include "Logger.h"
#include "Cue.h"
#include "ParserUtil.h"
#include "Parser.h"
#include "constants.h"

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
        preProcessingThread->join();
        parsingThread->join();
    };

    void Parser::cleanDecodedData(std::u32string &input)
    {
        if (input.empty())
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
            bool haveNext = std::next(current) != end;
            uint32_t next_c = haveNext ? *current : 0;

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
                auto temp = current;
                std::advance(current, 1);
                input.erase(temp);
            }
            else
                std::advance(current, 1);
        }
    }

    void Parser::preProcessDecodedStreamLoop()
    {
        std::string buffer;
        std::u32string decodedData;
        while (true)
        {
            decodedData = inputStream->readMultiple(DEFAULT_READ_NUMBER);

            if (decodedData.length() == 0)
            {
                break;
            }
            cleanDecodedData(decodedData);

            preprocessedStream->writeMultiple(decodedData);
        };
        preprocessedStream->setInputEnded();
    };

    std::unique_ptr<Block> Parser::collectBlock(bool inHeader)
    {
        //[Collect WebVTT Block] Step 1-10
        uint32_t lineCount = 0;
        //Problem when return end of stream???
        auto previousPosition = preprocessedStream->getReadPosition();
        std::u32string line;
        std::u32string buffer;
        bool seenEOF = false, seenArrow = false;

        //Cue, stylesheet, region = null;
        std::unique_ptr<Cue> newCue = nullptr;
        std::unique_ptr<StyleSheet> newStyleSheet = nullptr;
        std::unique_ptr<Region> newRegion = nullptr;

        //[Collect WebVTT Block] Step 11
        while (true)
        {
            //[Collect WebVTT Block] Step 11.1
            auto readData = preprocessedStream->readUntilSpecificData(LF_C);
            if (!readData.empty())
                line = readData;

            //[Collect WebVTT Block] Step 11.2
            lineCount++;

            //[Collect WebVTT Block] Step 11.3
            auto readOneDataOptional = preprocessedStream->isReadDoneAndAdvancedIfNot();
            if (!readOneDataOptional.has_value())
                seenEOF = true;

            readOneDataOptional = preprocessedStream->peekOne();

            //[Collect WebVTT Block] Step 11.4
            bool lineContainArrow = ParserUtil::stringContainsSeparator(line, TIME_STAMP_SEPARATOR);
            if (lineContainArrow)
            {

                //[Collect WebVTT Block] Step 11.4.1
                if (!inHeader and (lineCount == 1 || lineCount == 2 && !seenArrow))
                {

                    //[Collect WebVTT Block] Step  11.4.1.1
                    seenArrow = true;

                    //TODO Check
                    //[Collect WebVTT Block] Step 11.4.1.2
                    preprocessedStream->clearBufferUntilReadPosition();
                    previousPosition = preprocessedStream->getReadPosition();

                    //[Collect WebVTT Block] Step 11.4.1.3
                    newCue = std::make_unique<Cue>(buffer);

                    //Need to add regions to use
                    //[Collect WebVTT Block] Step 11.4.1.4
                    auto position = std::u32string_view(line).begin();
                    bool success = newCue->collectTimingAndSettings(line, position);
                    if (!success)
                    {
                        newCue = nullptr;
                    }
                    else
                    {
                        buffer.clear();
                        seenCue = true;
                    }
                    //Collect cue info from line
                }
                else
                {
                    //[Collect WebVTT Block] Step 11.4.2.1
                    preprocessedStream->setReadPosition(previousPosition);
                    break;
                }
            }
            //[Collect WebVTT Block] Step 11.5
            else if (line.length() == 0)
                break;
            //[Collect WebVTT Block] Step 11.6
            else
            {
                //[Collect WebVTT Block] Step 11.6.1
                if (!inHeader and lineCount == 2)
                {

                    //[Collect WebVTT Block] Step 11.6.1.1
                    if (!seenCue && ParserUtil::stringEqualStringPlusSpaces(buffer, STYLE_NAME))
                    {
                        //[Collect WebVTT Block] Step 11.6.1.1.1
                        newStyleSheet = std::make_unique<StyleSheet>();
                        //[Collect WebVTT Block] Step 11.6.1.2
                        buffer.clear();
                    }
                    //[Collect WebVTT Block] Step 11.6.1.2
                    if (!seenCue && ParserUtil::stringEqualStringPlusSpaces(buffer, REGION_NAME))
                    {
                        newRegion = std::make_unique<Region>();
                        buffer.clear();
                    }
                }

                //[Collect WebVTT Block] Step 11.6.2
                if (!buffer.empty())
                    buffer.push_back(LF_C);

                //[Collect WebVTT Block] Step 11.6.3
                buffer.append(line);

                //[Collect WebVTT Block] Step 11.6.4
                previousPosition = preprocessedStream->getReadPosition();
            }
            //[Collect WebVTT Block] Step 11.7
            if (seenEOF)
                break;
        }

        //[Collect WebVTT Block] Step 12
        if (newCue)
        {
            newCue->setText(buffer);
            auto temp = utf8::utf32to8(buffer);
            parserLogger.info("Found cue");
            parserLogger.info(temp);
            return newCue;
        }
        if (newStyleSheet)
        {
            //TODO Collect style sheets from buffer and add it to style sheets list
            return newStyleSheet;
        }
        if (newRegion)
        {
            //TODO Collect regions from buffer and add it to regions list
            return newRegion;
        }

        return nullptr;
    }

    bool Parser::startParsing()
    {
        if (parsingStarted)
            return false;
        parsingStarted = true;
        preProcessingThread = std::make_unique<std::thread>(&Parser::preProcessDecodedStreamLoop, this);
        parsingThread = std::make_unique<std::thread>(&Parser::parsingLoop, this);
        return true;
    }

    void Parser::parsingLoop()
    {
        bool fileIsOK = true;

        std::u32string readData;
        std::optional<uint32_t> readOneDataOptional;

        while (true)
        {
            //[Main loop] Steps [2-6]
            readData = preprocessedStream->readMultiple(EXTENSION_NAME_LENGTH);
            if (readData != EXTENSION_NAME)
            {
                fileIsOK = false;
                break;
            }

            readOneDataOptional = preprocessedStream->isReadDoneAndAdvancedIfNot();
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
            preprocessedStream->readUntilSpecificData(LF_C);

            //[Main loop] Step [8-9]
            readOneDataOptional = preprocessedStream->isReadDoneAndAdvancedIfNot();
            if (!readOneDataOptional.has_value())
            {
                break;
            }

            //[Main loop] Step 10
            if (preprocessedStream->isReadDone())
            {
                break;
            }

            //[Main loop] [Header] Step 11
            readOneDataOptional = preprocessedStream->peekOne();
            if (readOneDataOptional.value() != LF_C)
            {
                collectBlock(true);
            }
            else
            {
                readOneDataOptional = preprocessedStream->readNext();
            }

            //[Main loop] Step 12
            preprocessedStream->readWhileSpecificData(LF_C);

            //[Main loop] Step 14
            readOneDataOptional = preprocessedStream->peekOne();
            while (readOneDataOptional.has_value())
            {
                //[Block loop] Step1
                auto newBlock = collectBlock(false);
                //Collected block was put in list inside the function

                //[Block loop] Step 5
                preprocessedStream->readWhileSpecificData(LF_C);
                readOneDataOptional = preprocessedStream->peekOne();
            }
            break;
        }
        if (!fileIsOK)
        {
            parserLogger.error("Error while parsing!\n");
            return;
        }
        else
        {
            parserLogger.info("Parsing successful!\n");
            return;
        }
    }

}