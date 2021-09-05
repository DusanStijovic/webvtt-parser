#ifndef LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
#include "buffer/IBuffer.hpp"

namespace webvtt {
template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
class NonSyncBuffer : public IBuffer<
    StoredDataType, DataTypeToCompare,
    ReceivedDataType, SendDataType,
    ReceivedMultipleType, SendMultipleType> {
 public:

  bool writeNext(ReceivedDataType x) override;
  SendDataType readNext() override;

  virtual SendDataType isReadDoneAndAdvancedIfNot();

  void clearBufferUntilReadPosition() override;
  void resetBuffer() override;

  bool setReadPosition(typename std::list<StoredDataType>::const_iterator position) override;
  typename std::list<StoredDataType>::const_iterator &getReadPosition() override;

  bool isInputEnded() override;
  void setInputEnded() override;
  bool isReadDone() override;

  SendDataType peekOne();

 protected:

  virtual void acceptDataToBuffer(ReceivedDataType x);
  virtual SendDataType sendDataType();
  virtual SendDataType sendDataTypeNoValue();

  SendDataType readOne() override;
  bool writeOne(ReceivedDataType x) override;

  bool inputEnded = false;
};
template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
bool NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::writeNext(ReceivedDataType x) {
  return writeOne(std::forward<ReceicedDataType>(x));
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
SendDataType NonSyncBuffer<StoredDataType,
                           DataTypeToCompare,
                           ReceivedDataType,
                           SendDataType,
                           ReceivedMultipleType,
                           SendMultipleType>::readNext() {
  return readOne();
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
SendDataType NonSyncBuffer<StoredDataType,
                           DataTypeToCompare,
                           ReceivedDataType,
                           SendDataType,
                           ReceivedMultipleType,
                           SendMultipleType>::isReadDoneAndAdvancedIfNot() {
  return readNext();
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
void NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::clearBufferUntilReadPosition() {
  this->buffer.erase(this->buffer.begin(), this->readPosition);
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
void NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::resetBuffer() {
  this->buffer.clear();
  this->readPosition = this->buffer.begin();
  this->inputEnded = false;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
bool NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::setReadPosition(std::list<StoredDataType>::const_iterator position) {
  this->readPosition = position;
  return true;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
std::list<StoredDataType>::const_iterator &NonSyncBuffer<StoredDataType,
                                                         DataTypeToCompare,
                                                         ReceivedDataType,
                                                         SendDataType,
                                                         ReceivedMultipleType,
                                                         SendMultipleType>::getReadPosition() {
  return this->readPosition;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
bool NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::isInputEnded() {
  return this->inputEnded;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
void NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::setInputEnded() {
  this->inputEnded = true;
}
template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
bool NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::isReadDone() {
  if (this->readPosition == this->buffer.end() && isInputEnded) return true;
  return false;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
SendDataType NonSyncBuffer<StoredDataType,
                           DataTypeToCompare,
                           ReceivedDataType,
                           SendDataType,
                           ReceivedMultipleType,
                           SendMultipleType>::peekOne() {
  if (this->readPosition != this->buffer.end()) {
    return sendDataType();
  }
  return sendDataTypeNoValue();
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
void NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::acceptDataToBuffer(ReceivedDataType x) {
  this->buffer.push_back(x);
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
SendDataType NonSyncBuffer<StoredDataType,
                           DataTypeToCompare,
                           ReceivedDataType,
                           SendDataType,
                           ReceivedMultipleType,
                           SendMultipleType>::sendDataType() {
  return *this->readPosition;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
bool NonSyncBuffer<StoredDataType,
                   DataTypeToCompare,
                   ReceivedDataType,
                   SendDataType,
                   ReceivedMultipleType,
                   SendMultipleType>::writeOne(ReceivedDataType x) {
  try {
    bool shouldRetBack = false;
    if (this->inputEnded)
      return false;

    //All data already read
    if (this->readPosition == this->buffer.end())
      shouldRetBack = true;

    acceptDataToBuffer(std::forward<ReceivedDataType>(x));

    if (shouldRetBack)
      this->readPosition = --this->buffer.end();

    return true;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    this->setInputEnded();
    throw;
  }
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
SendDataType NonSyncBuffer<StoredDataType,
                           DataTypeToCompare,
                           ReceivedDataType,
                           SendDataType,
                           ReceivedMultipleType,
                           SendMultipleType>::readOne() {
  SendDataType res = this->sendDataTypeNoValue();

  if (this->readPosition == this->buffer.end())
    return this->sendDataTypeNoValue();

  res = this->sendDataType();
  std::advance(this->readPosition, 1);

  return res;
}

template<
    typename StoredDataType, typename DataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
SendDataType NonSyncBuffer<StoredDataType,
                           DataTypeToCompare,
                           ReceivedDataType,
                           SendDataType,
                           ReceivedMultipleType,
                           SendMultipleType>::sendDataTypeNoValue() {
  return std::nullopt;
}

} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/NonSyncBuffer.tpp"
#endif // LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
