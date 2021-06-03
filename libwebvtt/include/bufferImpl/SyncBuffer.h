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
    SyncBuffer();

    bool writeOne(dataType x);
    bool writeNext(dataType x);
    bool writeMultiple(StringType input);

    std::optional<dataType> readNext();
    std::optional<dataType> readOne();
    StringType readMultiple(uint32_t number);
    StringType readUntilSpecificData(dataType specificData);
    StringType readWhileSpecificData(dataType specificData);
    std::optional<dataType> peekOne();

    void clearBufferUntilReadPosition();

    bool setReadPosition(typename std::list<dataType>::iterator position);
    typename std::list<dataType>::iterator getReadPosition();

    bool isInputEnded();
    void setInputEnded();

    //uint32_t getSize() { return leftToRead; }

    std::optional<dataType> isReadDoneAndAdvancedIfNot();

    bool isReadDone();

private:
    constexpr static int NUM_OF_SLOTS = 10;

    std::list<dataType> buffer;
    typename std::list<dataType>::iterator readPosition;

    std::condition_variable emptyCV;
    std::mutex mutex;

    std::mutex mutexWrite;
    std::mutex mutexRead;

    bool inputEnded = false;
    //uint32_t leftToRead = 0;
};

#endif