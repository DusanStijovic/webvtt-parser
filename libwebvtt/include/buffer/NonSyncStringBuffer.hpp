#ifndef LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
#include "buffer/StringBuffer.hpp"

namespace webvtt {
template<typename OneElemType>
class NonSyncStringBuffer : public StringBuffer<OneElemType> {
 public:

  bool isInputEnded() override;
  void setInputEnded() override;
  bool isReadDone() override;

  std::optional <OneElemType> peekOne() override;

 protected:

  std::optional <OneElemType> readOne() override;
  bool writeOne(const OneElemType &elem) override;

};


} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/NonSyncBuffer.tpp"
#endif // LIBWEBVTT_INCLUDE_BUFFER_NON_SYNC_BUFFER_HPP_
