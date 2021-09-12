
#include "utf8.h"
#include <optional>
#include <list>
#include <buffer/StringSyncBuffer.hpp>

#include "logger/LoggingUtility.hpp"

namespace webvtt {

template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::isInputEnded() {
  std::lock_guard<std::mutex> lock(this->mutex);
  return this->inputEnded;
}
template<typename OneElemType>
void StringSyncBuffer<OneElemType>::setInputEnded() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->inputEnded = true;
  this->emptyCV.notify_all();
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::isReadDone() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (this->readPosition == this->buffer.length() && !this->inputEnded)
    this->emptyCV.wait(lock);

  bool retVal = this->readPosition == this->buffer.length();
  this->emptyCV.notify_all();
  return retVal;
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::writeNext(const OneElemType &elem) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  return StringBuffer<OneElemType>::writeNext(elem);
}
template<typename OneElemType>
std::optional<OneElemType> StringSyncBuffer<OneElemType>::readNext() {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  return StringBuffer<OneElemType>::readNext();
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::writeMultiple(const std::basic_string<OneElemType> &input) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  return StringBuffer<OneElemType>::writeMultiple(input);
}
template<typename OneElemType>
std::basic_string<OneElemType> StringSyncBuffer<OneElemType>::readMultiple(uint32_t number) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  return StringBuffer<OneElemType>::readMultiple(number);

}
template<typename OneElemType>
std::basic_string<OneElemType> StringSyncBuffer<OneElemType>::readUntilSpecificData(const OneElemType &specificData) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  return StringBuffer<OneElemType>::readUntilSpecificData(specificData);
}
template<typename OneElemType>
std::basic_string<OneElemType> StringSyncBuffer<OneElemType>::readWhileSpecificData(const OneElemType &specificData) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  return StringBuffer<OneElemType>::readWhileSpecificData(specificData);
}
template<typename OneElemType>
std::optional<OneElemType> StringSyncBuffer<OneElemType>::isReadDoneAndAdvancedIfNot() {
  return StringBuffer<OneElemType>::isReadDoneAndAdvancedIfNot();
}
template<typename OneElemType>
size_t StringSyncBuffer<OneElemType>::getReadPosition() {
  this->isReadDone();
  return this->readPosition;
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::setReadPosition(size_t position) {
  std::lock_guard<std::mutex> lock(this->mutex);
  return StringBuffer<OneElemType>::setReadPosition(position);
}
template<typename OneElemType>
void StringSyncBuffer<OneElemType>::clearBufferUntilReadPosition() {
  std::lock_guard<std::mutex> lock(this->mutex);
  StringBuffer<OneElemType>::clearBufferUntilReadPosition();

}
template<typename OneElemType>
void StringSyncBuffer<OneElemType>::resetBuffer() {
  std::lock_guard<std::mutex> lock(this->mutex);
  StringBuffer<OneElemType>::resetBuffer();
}
template<typename OneElemType>
std::optional<OneElemType> StringSyncBuffer<OneElemType>::readOne() {
  std::unique_lock<std::mutex> lock(this->mutex);

  while (this->readPosition == this->buffer.length() && !this->inputEnded)
    this->emptyCV.wait(lock);

  if (this->readPosition == this->buffer.length())
    return std::nullopt;

  auto res = this->buffer[this->readPosition];
  this->readPosition++;

  return res;
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::writeOne(const OneElemType &elem) {
  try {
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->inputEnded)
      return false;

    this->buffer.push_back(elem);

    this->emptyCV.notify_all();
    return true;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    this->setInputEnded();
    throw;
  }
}
template<typename OneElemType>
std::optional<OneElemType> StringSyncBuffer<OneElemType>::peekOne() {
  std::unique_lock<std::mutex> lock(this->mutex);

  while (this->readPosition == this->buffer.length() && !this->inputEnded)
    this->emptyCV.wait(lock);

  if (this->readPosition == this->buffer.length())
    return std::nullopt;

  auto res = this->buffer[this->readPosition];

  return res;
}

}
