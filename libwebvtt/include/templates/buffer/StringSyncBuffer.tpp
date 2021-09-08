
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
bool StringSyncBuffer<OneElemType>::writeNext(OneElemType x) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  return writeOne(x);
}
template<typename OneElemType>
std::optional<OneElemType> StringSyncBuffer<OneElemType>::readNext() {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  return this->readOne();
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::writeMultiple(std::basic_string<OneElemType> &input) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  bool success;
  for (auto one : input) {
    success = this->writeOne(one);
    if (!success)
      return false;
  }
  return true;
}
template<typename OneElemType>
std::basic_string<OneElemType> StringSyncBuffer<OneElemType>::readMultiple(uint32_t number) {
  std::lock_guard<std::mutex> lock(this->mutexRead);

  std::basic_string<OneElemType> values;
  for (uint32_t i = 0; i < number; i++) {
    auto result = this->readOne();
    if (result.has_value()) {
      values.push_back(result.value());
    } else
      return values;
  }
  return values;
}
template<typename OneElemType>
std::basic_string<OneElemType> StringSyncBuffer<OneElemType>::readUntilSpecificData(OneElemType specificData) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  std::basic_string<OneElemType> values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() != specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}
template<typename OneElemType>
std::basic_string<OneElemType> StringSyncBuffer<OneElemType>::readWhileSpecificData(OneElemType specificData) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  std::basic_string<OneElemType> values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() == specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}
template<typename OneElemType>
std::optional<OneElemType> StringSyncBuffer<OneElemType>::isReadDoneAndAdvancedIfNot() {
  return readNext();
}
template<typename OneElemType>
size_t StringSyncBuffer<OneElemType>::getReadPosition() {
  this->isReadDone();
  return this->readPosition;
}
template<typename OneElemType>
bool StringSyncBuffer<OneElemType>::setReadPosition(size_t position) {
  std::lock_guard<std::mutex> lock(this->mutex);
  if (position > this->buffer.length()) return false;
  this->readPosition = position;
  return true;
}
template<typename OneElemType>
void StringSyncBuffer<OneElemType>::clearBufferUntilReadPosition() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->buffer.erase(this->buffer.begin(), this->buffer.begin() + this->readPosition);
  this->readPosition = 0;

}
template<typename OneElemType>
void StringSyncBuffer<OneElemType>::resetBuffer() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->buffer.clear();
  this->readPosition = 0;
  this->inputEnded = false;
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
bool StringSyncBuffer<OneElemType>::writeOne(OneElemType elem) {
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
