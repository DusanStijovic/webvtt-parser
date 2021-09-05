#ifndef LIBWEBVTT_INCLUDE_BUFFER_I_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_I_BUFFER_HPP_

#include <list>

namespace webvtt {

template<
    typename StoredDataType, typename DataToCompareType,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType>
class IBuffer {
 public:
  virtual bool isInputEnded() = 0;
  virtual void setInputEnded() = 0;
  virtual bool isReadDone() = 0;

  virtual bool writeMultiple(ReceivedMultipleType input) = 0;
  virtual SendMultipleType readMultiple(uint32_t number) = 0;

  virtual SendMultipleType readUntilSpecificData(DataToCompareType specificData) = 0;
  virtual SendMultipleType readWhileSpecificData(DataToCompareType specificData) = 0;

  virtual bool writeNext(ReceivedDataType x) = 0;
  virtual SendDataType readNext() = 0;

  virtual SendDataType isReadDoneAndAdvancedIfNot() = 0;

  virtual typename std::list<StoredDataType>::const_iterator &getReadPosition() = 0;
  virtual bool setReadPosition(typename std::list<StoredDataType>::const_iterator position) = 0;
  virtual void clearBufferUntilReadPosition() = 0;
  virtual void resetBuffer() = 0;

  IBuffer();
  IBuffer(const IBuffer &) = delete;
  IBuffer(IBuffer &&) = delete;
  IBuffer &operator=(const IBuffer &) = delete;
  IBuffer &operator=(IBuffer &&) = delete;

 protected:

  virtual SendDataType readOne() = 0;
  virtual bool writeOne(ReceivedDataType x) = 0;

  std::list<StoredDataType> buffer;
  typename std::list<StoredDataType>::const_iterator readPosition;

  bool inputEnded = false;
};

} // namespace webvtt

#include "templates/buffer/IBuffer.tpp"
#endif // LIBWEBVTT_INCLUDE_BUFFER_I_BUFFER_HPP_
