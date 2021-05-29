#ifndef SYNC_BUFFER_H
#define SYNC_BUFFER_H

#include "Semaphore.h"
#include <vector>
#include <array>
#include <mutex>
#include <optional>
#include <list>

template <typename StringType, typename dataType>
class SyncBuffer
{
public:
    SyncBuffer()
    {
        //static_assert(std::is_same<StringType, std::u32string>::value && std::is_same<dataType, uint32_t>::value, "Incompatible types");
        //static_assert(std::is_same<StringType, std::string>::value && std::is_same<dataType, uint8_t>::value, "Incompatible types");
    }

    bool writeOne(dataType x);
    bool writeNext(dataType x);
    bool writeMultiple(StringType input);

    std::optional<dataType> readNext();
    std::optional<dataType> readOne();
    StringType readMultiple(uint32_t number);
    StringType readUntilSpecificData(dataType specificData);
    std::optional<dataType> peekOne();

    bool isInputEnded();
    void setInputEnded();

    uint32_t getSize() { return leftToRead; }

    std::optional<dataType> isReadDoneAndAdvancedIfNot();
    bool isReadDone();

private:
    constexpr static int NUM_OF_SLOTS = 10;
    std::array<dataType, NUM_OF_SLOTS> buffer;

    int m_w = 0;
    int m_r = 0;
    std::condition_variable notFull;
    std::condition_variable notEmpty;
    std::mutex mutexWrite;
    std::mutex mutexRead;
    std::mutex mutex;
    bool inputEnded = false;
    uint32_t leftToRead = 0;
};

#endif