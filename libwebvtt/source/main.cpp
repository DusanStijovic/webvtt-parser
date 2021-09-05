#include "parser/Parser.hpp"
#include "parser/ParserUtil.hpp"
#include "buffer/StringSyncBuffer.hpp"
#include "decoder/UTF8ToUTF32StreamDecoder.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <memory.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

void writeToBuffer(const std::shared_ptr<webvtt::StringSyncBuffer<std::string, uint8_t>> &buffer,
                   const std::string &input) {
  for (auto oneChar : input) {
    buffer->writeNext(oneChar);
    std::this_thread::sleep_for(2ms);
  }
  buffer->setInputEnded();
}

int main(int argc, char *argv[]) {
  std::ifstream t("../example/sample.vtt", std::ios_base::in);

  if (!t.is_open()) {
    DILOGE("Error in file name");
    return -1;
  }
  std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  auto buffer = std::make_shared<webvtt::StringSyncBuffer<std::string, uint8_t>>();

  auto decoder = webvtt::UTF8ToUTF32StreamDecoder(buffer);
  decoder.startDecoding();
  // int x = 5;
  // std::cout << (x --< 0);

  auto parser = webvtt::Parser(decoder.getDecodedStream());

  auto streamThread = std::thread(writeToBuffer, buffer, str);

  parser.startParsing();

  streamThread.join();
  std::cout << "END" << std::endl;
}