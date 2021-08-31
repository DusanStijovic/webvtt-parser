#include "parser/Parser.h"
#include "parser/ParserUtil.h"
#include "buffer/StringSyncBuffer.h"
#include "decoder/UTF8ToUTF32StreamDecoder.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <memory.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

void writeToBuffer(const std::shared_ptr<WebVTT::StringSyncBuffer<std::string, uint8_t>> &buffer, const std::string &input)
{
    for (auto oneChar : input)
    {
        buffer->writeNext(oneChar);
        std::this_thread::sleep_for(2ms);
    }
    buffer->setInputEnded();
}

int main(int argc, char *argv[])
{
    std::ifstream t("../sample.vtt", std::ios_base::in);

    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    auto buffer = std::make_shared<WebVTT::StringSyncBuffer<std::string, uint8_t>>();

    auto decoder = WebVTT::UTF8ToUTF32StreamDecoder(buffer);
    decoder.startDecoding();
    // int x = 5;
    // std::cout << (x --< 0);

    auto parser = WebVTT::Parser(decoder.getDecodedStream());

    auto streamThread = std::thread(writeToBuffer, buffer, str);

    parser.startParsing();

    streamThread.join();
  std::cout << "END" << std::endl;
}