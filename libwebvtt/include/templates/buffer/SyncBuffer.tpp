#include "utf8.h"
#include <optional>
#include <list>
#include <buffer/SyncBuffer.hpp>

#include "logger/LoggingUtility.hpp"

namespace webvtt {

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
bool SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::writeNext(ReceivedDataType x) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  return this->writeOne(std::forward<ReceivedDataType>(x));
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
SendDataType SyncBuffer<StoredDataType,
                        DataTypeToCompare,
                        ReceivedDataType,
                        SendDataType,
                        ReceivedMultipleType,
                        SendMultipleType>::readNext() {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  return this->readOne();
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
bool SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::writeOne(ReceivedDataType x) {
  try {
    std::unique_lock<std::mutex> lock(this->mutex);
    bool shouldRetBack = false;
    if (this->inputEnded)
      return false;
    {
      //All data already read
      if (this->readPosition == this->buffer.end())
        shouldRetBack = true;

      acceptDataToBuffer(std::forward<ReceivedDataType>(x));

      if (shouldRetBack)
        this->readPosition = --this->buffer.end();
    }
    this->emptyCV.notify_all();
    return true;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    this->setInputEnded();
    throw;
  }
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
SendDataType SyncBuffer<StoredDataType,
                        DataTypeToCompare,
                        ReceivedDataType,
                        SendDataType,
                        ReceivedMultipleType,
                        SendMultipleType>::readOne() {
  std::unique_lock<std::mutex> lock(this->mutex);

  SendDataType res = this->sendDataTypeNoValue();

  while (this->readPosition == this->buffer.end() && !this->inputEnded)
    this->emptyCV.wait(lock);

  if (this->readPosition == this->buffer.end())
    return this->sendDataTypeNoValue();
  {
    res = this->sendDataType();
    std::advance(this->readPosition, 1);
  }
  return res;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
SendDataType SyncBuffer<StoredDataType,
                        DataTypeToCompare,
                        ReceivedDataType,
                        SendDataType,
                        ReceivedMultipleType,
                        SendMultipleType>::peekOne() {
  std::unique_lock<std::mutex> lock(this->mutex);

  while (this->readPosition == this->buffer.end() && !this->inputEnded)
    this->emptyCV.wait(lock);

  if (this->readPosition == this->buffer.end())
    return this->sendDataTypeNoValue();

  auto res = this->sendDataType();

  this->emptyCV.notify_all();
  return res;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
bool SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::isInputEnded() {
  std::lock_guard<std::mutex> l(this->mutex);
  return this->inputEnded;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
void SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::setInputEnded() {
  std::lock_guard<std::mutex> l(this->mutex);
  this->inputEnded = true;
  this->emptyCV.notify_all();
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
bool SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::isReadDone() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (this->readPosition == this->buffer.end() && !this->inputEnded)
    this->emptyCV.wait(lock);
  bool retVal = this->readPosition == this->buffer.end();
  this->emptyCV.notify_all();
  return retVal;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
bool SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::setReadPosition(typename std::list<StoredDataType>::const_iterator position) {
  std::scoped_lock lock(mutex);
  if (position == this->buffer.end())
    return false;

  this->readPosition = position;
  return true;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
typename std::list<StoredDataType>::const_iterator &SyncBuffer<StoredDataType,
                                                               DataTypeToCompare,
                                                               ReceivedDataType,
                                                               SendDataType,
                                                               ReceivedMultipleType,
                                                               SendMultipleType>::getReadPosition() {
  this->isReadDone();
  return this->readPosition;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
void SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::clearBufferUntilReadPosition() {
  std::scoped_lock lock(mutex);
  this->buffer.erase(this->buffer.begin(), this->readPosition);
}

template<typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType>
void SyncBuffer<StoredDataType,
                DataTypeToCompare,
                ReceivedDataType,
                SendDataType,
                ReceivedMultipleType,
                SendMultipleType>::resetBuffer() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->buffer.clear();
  this->readPosition = this->buffer.begin();
  this->inputEnded = false;
}

template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType>
SendDataType SyncBuffer<StoredDataType,
                        DataTypeToCompare,
                        ReceivedDataType,
                        SendDataType,
                        ReceivedMultipleType,
                        SendMultipleType>::isReadDoneAndAdvancedIfNot() {
  return this->readNext();
}

} // namespace webvtt
