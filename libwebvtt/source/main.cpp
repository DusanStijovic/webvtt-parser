#include "WebVTTParser.h"
#include "SyncBuffer.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <memory.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

using namespace WebVTT;

void writeToBuffer(const std::shared_ptr<SyncBuffer<std::string, uint8_t>> &buffer, const std::string &input)
{
    for (auto oneChar : input)
    {
        buffer.get()->writeTo(oneChar);
        std::this_thread::sleep_for(2ms);
    }
    buffer.get()->setInputEnded();
}

int main(int argc, char *argv[])
{
    std::ifstream t("sample.vtt", std::ios_base::in);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    //std::cout << str << std::flush;

    auto buffer = std::make_shared<SyncBuffer<std::string, uint8_t>>();
    auto parser = WebVTTParser(buffer);
    auto streamThread = std::thread(writeToBuffer, buffer, str);

    parser.parserRun();

    streamThread.join();
}