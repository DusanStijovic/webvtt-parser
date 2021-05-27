#include "SyncBuffer.h"
#include <memory>
#include <string>
#include <thread>
#include "Logger.h"

using namespace CPlusPlusLogging;

class UTF8ToUTF32StreamDecoder
{

public:
    UTF8ToUTF32StreamDecoder(std::shared_ptr<SyncBuffer<std::string, uint8_t>> inputStream) : inputStream(inputStream)
    {
        outputstream = std::make_shared<SyncBuffer<std::u32string, uint32_t>>();
        logger.updateLogType(CONSOLE);
    }
    ~UTF8ToUTF32StreamDecoder();

    bool startDecoding();
    std::optional<std::shared_ptr<SyncBuffer<std::u32string, uint32_t>>> getDecodedStream();

private:
    constexpr static int DEFAULT_READ_NUMBER = 10;
    bool decodingStarted = false;
    Logger logger{"decoding.log"};

    std::shared_ptr<SyncBuffer<std::string, uint8_t>> inputStream;
    std::shared_ptr<SyncBuffer<std::u32string, uint32_t>> outputstream;

    std::unique_ptr<std::thread> decoderThread;

    std::u32string decodeReadBytes(std::string &readBytes);
    void decodeInputStream();
};