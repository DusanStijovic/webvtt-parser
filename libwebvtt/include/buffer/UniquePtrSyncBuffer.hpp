#ifndef LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_HPP_
#include <memory>
#include <list>
#include <mutex>
#include <condition_variable>

namespace webvtt {

template<typename Elem>
class UniquePtrSyncBuffer {
 public:
  const Elem *getElemByID(std::u32string_view id) const;

  virtual const Elem *readOne();
  virtual bool writeOne(std::unique_ptr<Elem> oneElem);

  bool writeMultiple(std::list<std::unique_ptr<Elem>> &list);

  virtual const Elem *peekOne();

  bool isInputEnded();
  void setInputEnded();
  bool isReadDone();

  void clearBuffer();
  void setReadPositionToBeginning();

 protected:

  mutable std::mutex mutex;
  std::condition_variable emptyCV;

  std::mutex mutexWrite;

  std::list<std::unique_ptr<Elem>> buffer;
  typename std::list<std::unique_ptr<Elem>>::const_iterator readPosition;

  bool inputEnded = false;

};

} // End of namespace webvtt
#include "templates/buffer/UniquePtrSyncBuffer.tpp"

#endif //LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_HPP_