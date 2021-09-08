#ifndef LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
#include "buffer/IStringBuffer.hpp"

namespace webvtt {
template<typename OneElemType>
class NonSyncBuffer : public IStringBuffer<OneElemType> {
 public:

  bool isInputEnded() override;
  void setInputEnded() override;
  bool isReadDone() override;

  std::optional <OneElemType> peekOne() override;

  bool writeNext(OneElemType x) override;
  std::optional <OneElemType> readNext() override;

  bool writeMultiple(std::basic_string <OneElemType> &input) override;
  std::basic_string <OneElemType> readMultiple(uint32_t number) override;

  std::basic_string <OneElemType> readUntilSpecificData(OneElemType specificData) override;
  std::basic_string <OneElemType> readWhileSpecificData(OneElemType specificData) override;

  std::optional <OneElemType> isReadDoneAndAdvancedIfNot() override;

  size_t getReadPosition() override;
  bool setReadPosition(size_t position) override;

  void clearBufferUntilReadPosition() override;
  void resetBuffer() override;

 protected:

  std::optional <OneElemType> readOne() override;
  bool writeOne(const OneElemType &x) override;

};
template<typename OneElemType>
bool NonSyncBuffer<OneElemType>::isInputEnded() {
  return this->inputEnded;
}
template<typename OneElemType>
void NonSyncBuffer<OneElemType>::setInputEnded() {
  this->inputEnded = true;
}
template<typename OneElemType>
void NonSyncBuffer<OneElemType>::resetBuffer() {
  this->buffer.clear();
  this->readPosition = 0;
  this->inputEnded = false;
}
template<typename OneElemType>
void NonSyncBuffer<OneElemType>::clearBufferUntilReadPosition() {
  this->buffer.erase(this->buffer.begin(), this->buffer.begin() + this->readPosition);
}
template<typename OneElemType>
bool NonSyncBuffer<OneElemType>::setReadPosition(size_t position) {
  if (position > this->buffer.length()) return false;
  this->readPosition = position;
  return true;
}
template<typename OneElemType>
size_t NonSyncBuffer<OneElemType>::getReadPosition() {
  return this->readPosition;
}
template<typename OneElemType>
std::optional <OneElemType> NonSyncBuffer<OneElemType>::isReadDoneAndAdvancedIfNot() {
  return readNext();
}
template<typename OneElemType>
std::basic_string <OneElemType> NonSyncBuffer<OneElemType>::readWhileSpecificData(OneElemType specificData) {
  std::basic_string <OneElemType> values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() == specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}
template<typename OneElemType>
std::basic_string <OneElemType> NonSyncBuffer<OneElemType>::readUntilSpecificData(OneElemType specificData) {
  std::basic_string <OneElemType> values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() != specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}
template<typename OneElemType>
std::basic_string <OneElemType> NonSyncBuffer<OneElemType>::readMultiple(uint32_t number) {
  std::basic_string <OneElemType> values;
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
bool NonSyncBuffer<OneElemType>::writeMultiple(std::basic_string <OneElemType> &input) {
  bool success;
  for (auto one : input) {
    success = this->writeOne(one);
    if (!success)
      return false;
  }
  return true;
}
template<typename OneElemType>
std::optional <OneElemType> NonSyncBuffer<OneElemType>::peekOne() {

  if (this->readPosition == this->buffer.length())
    return std::nullopt;

  return this->buffer[this->readPosition];
}
template<typename OneElemType>
bool NonSyncBuffer<OneElemType>::writeNext(OneElemType x) {
  return writeOne(x);
}
template<typename OneElemType>
std::optional <OneElemType> NonSyncBuffer<OneElemType>::readNext() {
  return readOne();
}
template<typename OneElemType>
bool NonSyncBuffer<OneElemType>::isReadDone() {
  return this->readPosition == this->buffer.end() && this->inputEnded;

}
template<typename OneElemType>
bool NonSyncBuffer<OneElemType>::writeOne(const OneElemType &elem) {
  try {
    if (this->inputEnded)
      return false;

    this->buffer.push_back(elem);

    return true;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    this->setInputEnded();
    throw;
  }
}
template<typename OneElemType>
std::optional <OneElemType> NonSyncBuffer<OneElemType>::readOne() {

  if (this->readPosition == this->buffer.length())
    return std::nullopt;

  return this->buffer[this->readPosition++];

}













//template<
//    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
//SendDataType NonSyncBuffer<StoredDataType,
//                           DataTypeToCompare,
//                           ReceivedDataType,
//                           SendDataType,
//                           ReceivedMultipleType,
//                           SendMultipleType>::sendDataTypeNoValue() {
//  return std::nullopt;
//}

} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/NonSyncBuffer.tpp"
#endif // LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
