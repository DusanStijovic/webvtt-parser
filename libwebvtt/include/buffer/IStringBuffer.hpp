#ifndef LIBWEBVTT_INCLUDE_BUFFER_I_STRING_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_I_STRING_BUFFER_HPP_
#include <optional>
#include <string>

namespace webvtt {

template<typename OneElemType>
class IStringBuffer {
 public:
  virtual bool isInputEnded() = 0;
  virtual void setInputEnded() = 0;
  virtual bool isReadDone() = 0;

  virtual std::optional<OneElemType> peekOne() = 0;

  virtual bool writeNext(OneElemType x) = 0;
  virtual std::optional<OneElemType> readNext() = 0;

  virtual bool writeMultiple(std::basic_string<OneElemType> &input) = 0;
  virtual std::basic_string<OneElemType> readMultiple(uint32_t number) = 0;

  virtual std::basic_string<OneElemType> readUntilSpecificData(OneElemType specificData) = 0;
  virtual std::basic_string<OneElemType> readWhileSpecificData(OneElemType specificData) = 0;

  virtual std::optional<OneElemType> isReadDoneAndAdvancedIfNot() = 0;

  virtual size_t getReadPosition() = 0;
  virtual bool setReadPosition(size_t position) = 0;
  virtual void clearBufferUntilReadPosition() = 0;
  virtual void resetBuffer() = 0;
 protected:
  std::basic_string<OneElemType> buffer;
  size_t readPosition = 0;
  bool inputEnded = false;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_BUFFER_I_STRING_BUFFER_HPP_
