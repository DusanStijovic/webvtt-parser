#include "decoder/UTF8ToUTF32StreamDecoder.hpp"
#include "utf8.h"
#include <thread>
#include "logger/LoggingUtility.hpp"

namespace webvtt {
UTF8ToUTF32StreamDecoder::UTF8ToUTF32StreamDecoder(std::shared_ptr<StringSyncBuffer<std::string, uint8_t>> inputStream)
    : inputStream(std::move(inputStream)) {
  outputStream = std::make_shared<StringSyncBuffer<std::u32string, uint32_t>>();
}

std::u32string UTF8ToUTF32StreamDecoder::decodeReadBytes(std::string &readBytes) {
  auto positionInvalid = utf8::find_invalid(readBytes);

  auto validUTF8 = std::string_view(readBytes);
  std::u32string utf_32;

  if (positionInvalid == std::string::npos) {
    utf_32 = utf8::utf8to32(validUTF8);
    readBytes.clear();
  } else {
    utf_32 = utf8::utf8to32(validUTF8.substr(0, positionInvalid));
    readBytes.erase(readBytes.begin(), readBytes.begin() + positionInvalid);
  }
  return utf_32;
}

void UTF8ToUTF32StreamDecoder::decodeInputStream() {
  std::string buffer;
  std::string bytes;

  try {

    while (true) {
      bytes = inputStream->readMultiple(DEFAULT_READ_NUMBER);

      if (bytes.length() == 0) {
        break;
      }
      buffer.append(bytes);
      std::u32string decodedBytes = decodeReadBytes(buffer);

      outputStream->writeMultiple(decodedBytes);
    }
    outputStream->setInputEnded();
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    outputStream->setInputEnded();
    inputStream->clearBufferUntilReadPosition();
    throw;
  }
};

bool UTF8ToUTF32StreamDecoder::startDecoding() {
  if (decodingStarted)
    return false;
  decodingStarted = true;
  decoderThread = std::make_unique<std::thread>(&UTF8ToUTF32StreamDecoder::decodeInputStream, this);
  return true;
};

std::shared_ptr<StringSyncBuffer<std::u32string, uint32_t>> UTF8ToUTF32StreamDecoder::getDecodedStream() {
  if (not decodingStarted)
    return nullptr;
  return outputStream;
};

UTF8ToUTF32StreamDecoder::~UTF8ToUTF32StreamDecoder() {
  if (not decodingStarted)
    return;
  decoderThread->join();
}
}