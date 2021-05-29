#include "UTF8ToUTF32StreamDecoder.h"
#include "utf8.h"
#include <thread>

std::u32string UTF8ToUTF32StreamDecoder::decodeReadBytes(std::string &readBytes)
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

void UTF8ToUTF32StreamDecoder::decodeInputStream()
{
    std::string buffer;
    std::string bytes;

    while (true)
    {
        bytes = inputStream.get()->readMultiple(DEFAULT_READ_NUMBER);

        if (bytes.length() == 0)
        {
            break;
        }
        buffer.append(bytes);
        std::u32string decodedBytes = decodeReadBytes(buffer);
        std::cout << std::flush;

        outputstream.get()->writeMultiple(decodedBytes);
    }
    outputstream.get()->setInputEnded();
    logger.info("end");
};

bool UTF8ToUTF32StreamDecoder::startDecoding()
{
    if (decodingStarted)
        return false;
    decodingStarted = true;
    decoderThread = std::make_unique<std::thread>(&UTF8ToUTF32StreamDecoder::decodeInputStream, this);

    return true;
};
std::optional<std::shared_ptr<SyncBuffer<std::u32string, uint32_t>>> UTF8ToUTF32StreamDecoder::getDecodedStream()
{
    if (not decodingStarted)
        return std::nullopt;
    return outputstream;
};

UTF8ToUTF32StreamDecoder::~UTF8ToUTF32StreamDecoder()
{
    //Videti da l je bezbedno uvek
    if (not decodingStarted)
        return;
    decoderThread.get()->join();
}
