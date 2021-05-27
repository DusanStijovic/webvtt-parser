#include "WebVTTParser.h"

#include <utf8.h>

#include <chrono>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <string_view>
#include <thread>
#include "Logger.h"

using namespace WebVTT;
using namespace CPlusPlusLogging;
using namespace std::chrono_literals;

/**
 * @author
 * @date 
 * @param 
 * @return
 */

WebVTTParser::WebVTTParser(std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> inputStream) : inputStream(inputStream)
{
    preprocessedStream = std::make_shared<SyncBuffer<std::u32string, uint32_t>>();
    parserLogger.updateLogType(LogType::CONSOLE);
};

void WebVTTParser::cleanDecodedData(std::u32string &input)
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

void WebVTTParser::preProcessDecodedStream()
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

bool WebVTTParser::checkIfStringContainsArrow(std::u32string input)
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

std::u32string WebVTTParser::collectWebVTTBlock(bool inHeader)
{
    uint32_t lineCount = 0;
    std::u32string line;
    std::u32string buffer;
    bool seenEOF = false, seenArrow = false;
    //Cue, stylesheet, region = null;

    while (true)
    {
        auto readData = preprocessedStream.get()->readUntilSpecificData(LF_C);
        if (readData.size() != 0)
            line = readData;

        lineCount++;

        if (preprocessedStream.get()->chechIfDoneAndAdvancedIfNot())
            seenEOF = true;

        if (line.size() == 0)
            break;

        bool lineContainArrow = checkIfStringContainsArrow(line);
        if (lineContainArrow)
        {
            if (not inHeader and (lineCount == 1 or lineCount == 2 and not seenArrow))
            {
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

void WebVTTParser::parserRun()
{
    auto one = std::thread(&WebVTTParser::preProcessDecodedStream, this);

    uint32_t position = 0;
    bool seenCue = false;
    bool fileIsOK = true;

    std::u32string readData;
    std::optional<uint32_t> readOneDataOptional;
    std::u32string EXTENSION_NAME = utf8::utf8to32(std::string_view("WEBVTT"));
    constexpr int EXTENSION_NAME_LENGTH = 6;

    while (true)
    {
        auto readData = preprocessedStream.get()->readMultiple(EXTENSION_NAME_LENGTH);
        if (readData != EXTENSION_NAME)
        {
            fileIsOK = false;
            break;
        }

        readOneDataOptional = preprocessedStream.get()->chechIfDoneAndAdvancedIfNot();
        if (!readOneDataOptional.has_value())
        {
            fileIsOK = false;
            break;
        }
        uint32_t readOne = readOneDataOptional.value();

        if (readOne != SPACE_C && readOne != LF_C && readOne != TAB_C)
        {
            fileIsOK = false;
            break;
        }

        preprocessedStream.get()->readUntilSpecificData(LF_C);

        readOneDataOptional = preprocessedStream.get()->chechIfDoneAndAdvancedIfNot();
        if (!readOneDataOptional.has_value())
        {
            break;
        }

        readOneDataOptional = preprocessedStream.get()->chechIfDoneAndAdvancedIfNot();
        if (readOneDataOptional.has_value())
        {
            break;
        }

        if (readOneDataOptional.value() != LF_C)
        {
        }
        else
        {
            readOneDataOptional = preprocessedStream.get()->readFrom();
        }
        preprocessedStream.get()->readUntilSpecificData(LF_C);
        //Regions

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

    one.join();
}
