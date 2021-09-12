#ifndef LIBWEBVTT_INCLUDE_BUFFER_STRING_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_STRING_SYNC_BUFFER_HPP_

#include <mutex>
#include <condition_variable>
#include <list>
#include <optional>
#include "buffer/StringBuffer.hpp"

namespace webvtt {
template<typename OneElemType>
class StringSyncBuffer : public StringBuffer<OneElemType> {
 public:
  bool isInputEnded() override;
  void setInputEnded() override;
  bool isReadDone() override;

  std::optional<OneElemType> peekOne() override;

  bool writeNext(const OneElemType &elem) override;
  std::optional<OneElemType> readNext() override;

  bool writeMultiple(const std::basic_string<OneElemType> &input) override;
  std::basic_string<OneElemType> readMultiple(uint32_t number) override;

  std::basic_string<OneElemType> readUntilSpecificData(const OneElemType &specificData) override;
  std::basic_string<OneElemType> readWhileSpecificData(const OneElemType &specificData) override;

  std::optional<OneElemType> isReadDoneAndAdvancedIfNot() override;

  size_t getReadPosition() override;
  bool setReadPosition(size_t position) override;

  void clearBufferUntilReadPosition() override;
  void resetBuffer() override;

 protected:

  bool writeOne(const OneElemType &elem) override;
  std::optional<OneElemType> readOne() override;

  std::mutex mutex;
  std::condition_variable emptyCV;

  std::mutex mutexWrite;
  std::mutex mutexRead;

};

} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/StringSyncBuffer.tpp"

#endif // LIBWEBVTT_INCLUDE_BUFFER_STRING_SYNC_BUFFER_HPP_