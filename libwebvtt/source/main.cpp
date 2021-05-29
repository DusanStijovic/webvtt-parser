#include "Parser.h"
#include "SyncBuffer.h"
#include "UTF8ToUTF32StreamDecoder.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <memory.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

void writeToBuffer(const std::shared_ptr<SyncBuffer<std::string, uint8_t>> &buffer, const std::string &input)
{
    for (auto oneChar : input)
    {
        buffer.get()->writeNext(oneChar);
        std::this_thread::sleep_for(2ms);
    }
    buffer.get()->setInputEnded();
}

int main(int argc, char *argv[])
{
    std::ifstream t("sample.vtt", std::ios_base::in);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    auto buffer = std::make_shared<SyncBuffer<std::string, uint8_t>>();

    auto decoder = UTF8ToUTF32StreamDecoder(buffer);
    decoder.startDecoding();

    auto parser = WebVTT::Parser(decoder.getDecodedStream().value());
    auto streamThread = std::thread(writeToBuffer, buffer, str);

    parser.startParsing();

    streamThread.join();
    while (1)
        ;
}