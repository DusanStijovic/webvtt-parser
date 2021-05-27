#include "SyncBuffer.h"
#include "utf8.h"
#include <optional>
#include <iostream>
#include <list>

template <typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::writeOne(dataType x)
{
    std::unique_lock<std::mutex> lock(mutex);
    while (leftToRead == NUM_OF_SLOTS && !inputEnded)
        notFull.wait(lock);
    if (inputEnded)
        return false;
    {
        buffer[m_w] = x;
        m_w = (m_w + 1) % NUM_OF_SLOTS == 0 ? 0 : m_w + 1;
        leftToRead++;
    }
    notEmpty.notify_all();
    return true;
}

template <typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::writeTo(dataType x)
{
    std::lock_guard<std::mutex> lock(mutexWrite);
    return writeOne(x);
}

template <typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::writeMultiple(StringType input)
{
    std::lock_guard<std::mutex> lock(mutexWrite);
    bool success;
    for (auto one : input)
    {
        success = writeOne(one);
        if (!success)
            return false;
    }
    return true;
}

template <typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::readOne()
{
    std::unique_lock<std::mutex> lock(mutex);

    int res = -1;
    while (leftToRead == 0 && !inputEnded)
        notEmpty.wait(lock);

    if (inputEnded && leftToRead == 0)
        return std::nullopt;
    {
        res = buffer[m_r];
        m_r = (m_r + 1) % NUM_OF_SLOTS == 0 ? 0 : m_r + 1;
        leftToRead--;
    }
    notFull.notify_all();
    return res;
}

template <typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::readFrom()
{
    std::lock_guard<std::mutex> lock(mutexRead);
    return readOne();
}

template <typename StringType, typename dataType>
StringType SyncBuffer<StringType, dataType>::readMultiple(uint32_t number)
{
    std::lock_guard<std::mutex> lock(mutexRead);
    StringType values;
    for (int i = 0; i < number; i++)
    {
        auto result = readOne();
        if (result.has_value())
        {
            values.push_back(result.value());
        }
        else
            return values;
    }
    return values;
}

template <typename StringType, typename dataType>
StringType SyncBuffer<StringType, dataType>::readUntilSpecificData(dataType specificData)
{
    std::lock_guard<std::mutex> lock(mutexRead);
    StringType values;
    auto result = readOne();
    while (result.has_value() && result.value() != specificData)
    {
        values.push_back(result.value());
        result = readFrom();
    }
    return values;
}

template <typename StringType, typename dataType>
bool SyncBuffer<StringType, dataType>::isInputEnded()
{
    std::lock_guard<std::mutex> l(mutex);
    return inputEnded;
}

template <typename StringType, typename dataType>
void SyncBuffer<StringType, dataType>::setInputEnded()
{
    std::lock_guard<std::mutex> l(mutex);
    inputEnded = true;
    notEmpty.notify_all();
}

template <typename StringType, typename dataType>
std::optional<dataType> SyncBuffer<StringType, dataType>::chechIfDoneAndAdvancedIfNot()
{

       return readFrom();
}

template class SyncBuffer<std::string, uint8_t>;
template class SyncBuffer<std::u32string, uint32_t>;