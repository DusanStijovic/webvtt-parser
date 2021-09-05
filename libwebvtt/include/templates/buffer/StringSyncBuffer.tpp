
#include "utf8.h"
#include <optional>
#include <list>
#include "logger/LoggingUtility.hpp"

namespace webvtt {

template<typename StringType, typename dataType>
bool StringSyncBuffer<StringType, dataType>::writeMultiple(StringType input) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  bool success;
  for (auto one : input) {
    success = this->writeOne(one);
    if (!success)
      return false;
  }
  return true;
}

template<typename StringType, typename dataType>
StringType StringSyncBuffer<StringType, dataType>::readMultiple(uint32_t number) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  StringType values;
  for (uint32_t i = 0; i < number; i++) {
    auto result = this->readOne();
    if (result.has_value()) {
      values.push_back(result.value());
    } else
      return values;
  }
  return values;
}

template<typename StringType, typename dataType>
StringType StringSyncBuffer<StringType, dataType>::readWhileSpecificData(dataType specificData) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  StringType values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() == specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}

template<typename StringType, typename dataType>
StringType StringSyncBuffer<StringType, dataType>::readUntilSpecificData(dataType specificData) {
  std::lock_guard<std::mutex> lock(this->mutexRead);
  StringType values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() != specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}

template<typename ContainerType, typename dataType>
std::optional<dataType> StringSyncBuffer<ContainerType, dataType>::sendDataType() {
  return *this->readPosition;
}
template<typename ContainerType, typename dataType>
void StringSyncBuffer<ContainerType, dataType>::acceptDataToBuffer(dataType value) {
  this->buffer.push_back(value);
}
template<typename ContainerType, typename dataType>
std::optional<dataType> StringSyncBuffer<ContainerType, dataType>::sendDataTypeNoValue() {
  return std::nullopt;
}

}
