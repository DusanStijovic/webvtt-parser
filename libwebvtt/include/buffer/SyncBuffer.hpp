#ifndef LIBWEBVTT_INCLUDE_BUFFER_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_SYNC_BUFFER_HPP_

#include "buffer/IBuffer.hpp"
#include <mutex>
#include <condition_variable>
#include <list>
#include <optional>

namespace webvtt {
template<
    typename StoredDataType, typename DataTypeToCompare,
    typename ReceivedDataType, typename SendDataType,
    typename ReceivedMultipleType, typename SendMultipleType
>
class SyncBuffer : public IBuffer<
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
  std::condition_variable emptyCV;
  std::mutex mutex;

  std::mutex mutexWrite;
  std::mutex mutexRead;

  virtual void acceptDataToBuffer(ReceivedDataType x) = 0;
  virtual SendDataType sendDataType() = 0;
  virtual SendDataType sendDataTypeNoValue() = 0;

  SendDataType readOne() override;
  bool writeOne(ReceivedDataType x) override;

};

} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/SyncBuffer.tpp"
#endif // LIBWEBVTT_INCLUDE_BUFFER_SYNC_BUFFER_HPP_
