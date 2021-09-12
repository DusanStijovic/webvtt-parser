#ifndef LIBWEBVTT_INCLUDE_BUFFER_I_STRING_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_I_STRING_BUFFER_HPP_
#include <optional>
#include <string>

namespace webvtt {

template<typename OneElemType>
class StringBuffer {
 public:
  virtual bool isInputEnded() = 0;
  virtual void setInputEnded() = 0;
  virtual bool isReadDone() = 0;

  virtual std::optional<OneElemType> peekOne() = 0;

  virtual bool writeNext(const OneElemType &elem);
  virtual std::optional<OneElemType> readNext();

  virtual bool writeMultiple(const std::basic_string<OneElemType> &input);
  virtual std::basic_string<OneElemType> readMultiple(uint32_t number);

  virtual std::basic_string<OneElemType> readUntilSpecificData(const OneElemType &specificData);
  virtual std::basic_string<OneElemType> readWhileSpecificData(const OneElemType &specificData);

  virtual std::optional<OneElemType> isReadDoneAndAdvancedIfNot();

  virtual size_t getReadPosition();
  virtual bool setReadPosition(size_t position);
  virtual void clearBufferUntilReadPosition();
  virtual void resetBuffer();
 protected:

  virtual std::optional<OneElemType> readOne() = 0;
  virtual bool writeOne(const OneElemType &x) = 0;

  std::basic_string<OneElemType> buffer;
  size_t readPosition = 0;
  bool inputEnded = false;
};

} // namespace webvtt

//Include implementation
#include "templates/buffer/StringBuffer.tpp"
#endif // LIBWEBVTT_INCLUDE_BUFFER_I_STRING_BUFFER_HPP_
