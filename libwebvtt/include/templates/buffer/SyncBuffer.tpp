#include "utf8.h"
#include <optional>
#include <list>
#include "logger/LoggingUtility.h"

namespace WebVTT
{

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  bool SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::writeNext(ReceivedDataType x)
  {
    std::lock_guard<std::mutex> lock(this->mutexWrite);
    return this->writeOne(std::forward<ReceivedDataType>(x));
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  SendDataType SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::readNext()
  {
    std::lock_guard<std::mutex> lock(this->mutexRead);
    return this->readOne();
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::SyncBuffer()
  {
    readPosition = buffer.begin();
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  bool SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::writeOne(ReceivedDataType x)
  {
    try
    {
      std::unique_lock<std::mutex> lock(mutex);
      bool shouldRetBack = false;
      if (inputEnded)
        return false;
      {
        //All data already read
        if (readPosition == buffer.end())
          shouldRetBack = true;

        acceptDataToBuffer(std::forward<ReceivedDataType>(x));

        if (shouldRetBack)
          readPosition = --buffer.end();
      }
      emptyCV.notify_all();
      return true;
    }
    catch (const std::bad_alloc &error)
    {
      DILOGE(error.what());
      setInputEnded();
      throw;
    }
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  SendDataType SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::readOne()
  {
    std::unique_lock<std::mutex> lock(mutex);

    SendDataType res = sendDataTypeNoValue();

    while (readPosition == buffer.end() && !inputEnded)
      emptyCV.wait(lock);

    if (readPosition == buffer.end())
      return sendDataTypeNoValue();
    {
      res = sendDataType();
      std::advance(readPosition, 1);
    }
    return res;
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  SendDataType SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::peekOne()
  {
    std::unique_lock<std::mutex> lock(mutex);

    while (readPosition == buffer.end() && !inputEnded)
      emptyCV.wait(lock);

    if (readPosition == buffer.end())
      return sendDataTypeNoValue();

    auto res = sendDataType();

    emptyCV.notify_all();
    return res;
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  bool SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::isInputEnded()
  {
    std::lock_guard<std::mutex> l(mutex);
    return inputEnded;
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  void SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::setInputEnded()
  {
    std::lock_guard<std::mutex> l(mutex);
    inputEnded = true;
    emptyCV.notify_all();
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  bool SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::isReadDone()
  {
    std::unique_lock<std::mutex> lock(mutex);
    while (readPosition == buffer.end() && not inputEnded)
      emptyCV.wait(lock);
    bool retVal = readPosition == buffer.end();
    emptyCV.notify_all();
    //Nema potrebe probudio(probudio je i ostale valjda) da ih ja budim.
    return retVal;
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  bool SyncBuffer<StoredDataType,
                  ReceivedDataType,
                  SendDataType>::setReadPosition(typename std::list<StoredDataType>::iterator position)
  {
    std::scoped_lock lock(mutex, mutexRead, mutexWrite);
    if (position == buffer.end())
      return false;

    readPosition = position;
    return true;
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  typename std::list<StoredDataType>::iterator SyncBuffer<StoredDataType,
                                                          ReceivedDataType,
                                                          SendDataType>::getReadPosition()
  {
    isReadDone();
    return readPosition;
  }

  template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
  void SyncBuffer<StoredDataType, ReceivedDataType, SendDataType>::clearBufferUntilReadPosition()
  {
    std::scoped_lock lock(mutex, mutexRead);
    buffer.erase(buffer.begin(), readPosition);
  }

}
