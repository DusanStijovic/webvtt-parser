#include "WebVTTParser.h"
#include "Logger.h"

#include <iostream>
#include <list>
#include <optional>
#include <utf8.h>
#include <string_view>
#include <thread>
#include <chrono>
#include <string>

using namespace WebVTT;
using namespace CPlusPlusLogging;
using namespace std::chrono_literals;

/**
 * @author
 * @date 
 * @param 
 * @return
 */

WebVTTParser::WebVTTParser(std::shared_ptr<SyncBuffer<std::string, u_int8_t>> inputBuffer) : inputBuffer(inputBuffer)
{
    decodedBuffer = std::make_shared<SyncBuffer<std::u32string, uint32_t>>();
};

void WebVTTParser::cleanDecodedBytes(std::u32string &input)
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

std::u32string WebVTTParser::decodeReadBytes(std::string &readBytes)
{
    auto positionInvalid = utf8::find_invalid(readBytes);

    std::string_view validUTF8 = std::string_view(readBytes);
    std::u32string utf_32;

    if (positionInvalid == std::string::npos)
    {
        utf_32 = utf8::utf8to32(validUTF8);
        readBytes.clear();
    }
    else
    {
        utf_32 = utf8::utf8to32(validUTF8.substr(0, positionInvalid));
        readBytes.erase(readBytes.begin(), readBytes.begin() + positionInvalid);
    }
    return utf_32;
}

void WebVTTParser::decodeInputStream()
{
    std::string buffer;
    std::string bytes;
    while (true)
    {
        bytes = inputBuffer.get()->readMultiple(DEFAULT_READ_NUMBER);

        if (bytes.length() == 0)
        {
            break;
        }
        buffer.append(bytes);
        std::u32string decodedBytes = decodeReadBytes(buffer);

        cleanDecodedBytes(decodedBytes);
        decodedBuffer.get()->writeMultiple(decodedBytes);
    }
    decodedBuffer.get()->setInputEnded();
};

std::u32string WebVTTParser::collectWebVTTBlock()
{
    uint32_t lineCount = 0;
    std::u32string line;
    std::u32string buffer;
    bool seenEOF = false, seenArrow = false;
    //Cue, stylesheet, region = null;
    while (true)
    {
        auto readData = decodedBuffer.get()->readUntilSpecificData(LF_C);
        if (readData.size() != 0)
            line = readData;
        lineCount++;
        if (decodedBuffer.get()->chechIfDoneAndAdvancedIfNot())
            seenEOF = true;
        else
            decodedBuffer.get()->readFrom();
    }
}

void WebVTTParser::parserRun()
{

    auto one = std::thread(&WebVTTParser::decodeInputStream, this);

    uint32_t position = 0;
    bool seenCue = false;
    bool fileIsOK = true;

    std::u32string readData;
    std::optional<uint32_t> readOneDataOptional;
    std::u32string EXTENSION_NAME = utf8::utf8to32(std::string_view("WEBVTT"));
    constexpr int EXTENSION_NAME_LENGTH = 6;

    while (true)
    {
        auto readData = decodedBuffer.get()->readMultiple(EXTENSION_NAME_LENGTH);
        if (readData != EXTENSION_NAME)
        {
            fileIsOK = false;
            break;
        }

        readOneDataOptional = decodedBuffer.get()->chechIfDoneAndAdvancedIfNot();
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

        decodedBuffer.get()->readUntilSpecificData(LF_C);

        readOneDataOptional = decodedBuffer.get()->chechIfDoneAndAdvancedIfNot();
        if (!readOneDataOptional.has_value())
        {
            break;
        }

        readOneDataOptional = decodedBuffer.get()->chechIfDoneAndAdvancedIfNot();
        if (readOneDataOptional.has_value())
        {
            break;
        }

        if (readOneDataOptional.value() != LF_C)
        {
        }
        else
        {
            readOneDataOptional = decodedBuffer.get()->readFrom();
        }

        break;
    }
    if (!fileIsOK)
    {
        std::cout << "Eror while parsing!\n";
    }
    else
    {
        std::cout << "Parsing sucessful!\n";
    }
    std::cout << std::flush;

    one.join();
}
