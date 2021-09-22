#include "parser/Parser.hpp"
#include "parser/ParserUtil.hpp"
#include "buffer/StringSyncBuffer.hpp"
//#include "buffer/NonSyncStringBuffer.hpp"
#include "decoder/UTF8ToUTF32StreamDecoder.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <memory.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <filesystem>

using namespace std::chrono_literals;

void writeToBuffer(const std::shared_ptr<webvtt::StringSyncBuffer<char8_t>> &buffer, const std::string &input) {
  for (auto oneChar : input) {
    buffer->writeNext(oneChar);
    std::this_thread::sleep_for(2ms);
  }
  buffer->setInputEnded();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    DILOGE("Accept only one argument");
    return -1;
  }

  if (!std::filesystem::exists(argv[1])) {
    DILOGE("Given file doesn't exist");
    return -1;
  }

  std::ifstream t(argv[1], std::ios_base::in);

  if (!t.is_open()) {
    DILOGE("Error in file opening");
    return -1;
  }
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  auto buffer = std::make_shared<webvtt::StringSyncBuffer<char8_t>>();

  auto decoder = webvtt::UTF8ToUTF32StreamDecoder(buffer);
  decoder.startDecoding();

  auto parser = webvtt::Parser(decoder.getDecodedStream());

  auto streamThread = std::thread(writeToBuffer, buffer, str);

  parser.startParsing();
  streamThread.join();
}