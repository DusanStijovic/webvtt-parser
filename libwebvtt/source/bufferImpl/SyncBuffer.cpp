#include "SyncBuffer.h"
#include "utf8.h"
#include <optional>
#include <list>

template<typename StringType, typename dataType>
SyncBuffer<StringType, dataType>::SyncBuffer() {
    //static_assert(std::is_same<StringType, std::u32string>::value && std::is_same<dataType, uint32_t>::value, "Incompatible types");
    //static_assert(std::is_same<StringType, std::string>::value && std::is_same<dataType, uint8_t>::value, "Incompatible types");
    readPosition = buffer.begin();
}

template<typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::writeOne(dataType x) {
    std::unique_lock<std::mutex> lock(mutex);
    bool shouldRetBack = false;
    if (inputEnded)
        return false;
    {
        if (readPosition == buffer.end())
            shouldRetBack = true;

        buffer.push_back(x);

        if (shouldRetBack)
            readPosition = --buffer.end();
    }
    emptyCV.notify_all();
    return true;
}

template<typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::writeNext(dataType x) {
    std::lock_guard<std::mutex> lock(mutexWrite);
    return writeOne(x);
}

template<typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::writeMultiple(StringType input) {
    std::lock_guard<std::mutex> lock(mutexWrite);
    bool success;
    for (auto one : input) {
        success = writeOne(one);
        if (!success)
            return false;
    }
    return true;
}

template<typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::readOne() {
    std::unique_lock<std::mutex> lock(mutex);

    dataType res = -1;

    while (readPosition == buffer.end() && !inputEnded)
        emptyCV.wait(lock);

    if (readPosition == buffer.end())
        return std::nullopt;
    {
        res = *readPosition;
        std::advance(readPosition, 1);
    }
    return res;
}

template<typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::peekOne() {
    std::unique_lock<std::mutex> lock(mutex);

    int res = -1;
    while (readPosition == buffer.end() && !inputEnded)
        emptyCV.wait(lock);

    if (readPosition == buffer.end())
        return std::nullopt;
    {
        res = *readPosition;
    }
    //TO DO, maybe yes maybe no
    emptyCV.notify_all();
    return res;
}

template<typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::readNext() {
    std::lock_guard<std::mutex> lock(mutexRead);
    return readOne();
}

template<typename StringType, typename dataType>
StringType SyncBuffer<StringType, dataType>::readMultiple(uint32_t number) {
    std::lock_guard<std::mutex> lock(mutexRead);
    StringType values;
    for (int i = 0; i < number; i++) {
        auto result = readOne();
        if (result.has_value()) {
            values.push_back(result.value());
        } else
            return values;
    }
    return values;
}

template<typename StringType, typename dataType>
StringType SyncBuffer<StringType, dataType>::readWhileSpecificData(dataType specificData) {
    std::lock_guard<std::mutex> lock(mutexRead);
    StringType values;

    auto result = peekOne();
    while (result.has_value() && result.value() == specificData) {
        result = readOne();
        values.push_back(result.value());
        result = peekOne();
    }
    return values;
}

template<typename StringType, typename dataType>
StringType SyncBuffer<StringType, dataType>::readUntilSpecificData(dataType specificData) {
    std::lock_guard<std::mutex> lock(mutexRead);
    StringType values;

    auto result = peekOne();
    while (result.has_value() && result.value() != specificData) {
        result = readOne();
        values.push_back(result.value());
        result = peekOne();
    }
    return values;
}

template<typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::isInputEnded() {
    std::lock_guard<std::mutex> l(mutex);
    return inputEnded;
}

template<typename StringType, typename dataType>
void SyncBuffer<StringType, dataType>::setInputEnded() {
    std::lock_guard<std::mutex> l(mutex);
    inputEnded = true;
    emptyCV.notify_all();
}

template<typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::isReadDoneAndAdvancedIfNot() {
    return readNext();
}

template<typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::isReadDone() {
    std::unique_lock<std::mutex> lock(mutex);
    while (readPosition == buffer.end() && not inputEnded)
        emptyCV.wait(lock);
    bool retVal = readPosition == buffer.end();
    emptyCV.notify_all();
    //Nema potrebe probudio(probudio je i ostale valjda) da ih ja budim.
    return retVal;
}

template<typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::setReadPosition(typename std::list<dataType>::iterator position) {
    std::scoped_lock lock(mutex, mutexRead, mutexWrite);
    if (position == buffer.end())
        return false;

    readPosition = position;
    return true;
}

template<typename StringType, typename dataType>
typename std::list<dataType>::iterator SyncBuffer<StringType, dataType>::getReadPosition() {
    isReadDone();
    return readPosition;
}

template<typename StringType, typename dataType>
void SyncBuffer<StringType, dataType>::clearBufferUntilReadPosition() {
    std::scoped_lock lock(mutex, mutexRead);
    buffer.erase(buffer.begin(), readPosition);
}

template
class SyncBuffer<std::string, uint8_t>;

template
class SyncBuffer<std::u32string, uint32_t>;


