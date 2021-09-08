
#include <algorithm>
#include "logger/LoggingUtility.hpp"
#include <buffer/UniquePtrSyncBuffer.hpp>
#include "exceptions/NotImplementedError.hpp"

namespace webvtt {

template<typename Elem>
const Elem *UniquePtrSyncBuffer<Elem>::getElemByID(std::u32string_view id) const {
  std::lock_guard<std::mutex> lock(this->mutex);
  // TODO Think why in reverse order
  auto found = std::find_if(this->buffer.rbegin(),
                            this->buffer.rend(),
                            [&id](const std::unique_ptr<Elem> &elem) {
                              return elem->getIdentifier() == id;
                            });
  if (found == this->buffer.rend())
    return nullptr;
  else
    return found->get();
}

template<typename Elem>
const Elem *UniquePtrSyncBuffer<Elem>::peekOne() {
  std::unique_lock<std::mutex> lock(this->mutex);

  while (this->readPosition == this->buffer.end() && !this->inputEnded)
    this->emptyCV.wait(lock);

  if (this->readPosition == this->buffer.end())
    return nullptr;

  auto res = (*this->readPosition).get();

  this->emptyCV.notify_all();
  return res;
};

template<typename Elem>
const Elem *UniquePtrSyncBuffer<Elem>::readOne() {
  std::unique_lock<std::mutex> lock(this->mutex);

  const Elem *res = nullptr;

  while (this->readPosition == this->buffer.end() && !this->inputEnded)
    this->emptyCV.wait(lock);

  if (this->readPosition == this->buffer.end())
    return nullptr;

  res = (*this->readPosition).get();
  std::advance(this->readPosition, 1);

  return res;
}

template<typename Elem>
bool UniquePtrSyncBuffer<Elem>::writeOne(std::unique_ptr<Elem> oneElem) {
  try {
    std::unique_lock<std::mutex> lock(this->mutex);
    bool shouldRetBack = false;
    if (this->inputEnded)
      return false;
    {
      //All data already read need to m
      if (this->readPosition == this->buffer.end())
        shouldRetBack = true;

      this->buffer.push_back(std::move(oneElem));

      if (shouldRetBack)
        this->readPosition = --this->buffer.end();
    }
    this->emptyCV.notify_all();
    return true;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    this->setInputEnded();
    throw;
  }

}

template<typename Elem>
bool UniquePtrSyncBuffer<Elem>::isInputEnded() {
  std::lock_guard<std::mutex> lock(this->mutex);
  return this->inputEnded;
}

template<typename Elem>
bool UniquePtrSyncBuffer<Elem>::writeMultiple(std::list<std::unique_ptr<Elem>> &list) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  for (auto &oneElem : list) {
    bool success = this->writeOne(std::move(oneElem));
    if (!success) return false;
  }
  list.clear();
  return true;
}

template<typename Elem>
bool UniquePtrSyncBuffer<Elem>::isReadDone() {
  std::unique_lock<std::mutex> lock(this->mutex);
  while (this->readPosition == this->buffer.end() && !this->inputEnded)
    this->emptyCV.wait(lock);

  bool retVal = this->readPosition == this->buffer.end();
  this->emptyCV.notify_all();
  return retVal;
}

template<typename Elem>
void UniquePtrSyncBuffer<Elem>::setInputEnded() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->inputEnded = true;
  this->emptyCV.notify_all();
}

template<typename Elem>
void UniquePtrSyncBuffer<Elem>::setReadPositionToBeginning() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->readPosition = this->buffer.begin();
}
template<typename Elem>
void UniquePtrSyncBuffer<Elem>::clearBuffer() {
  std::lock_guard<std::mutex> lock(this->mutex);
  this->buffer.clear();
  this->readPosition = this->buffer.begin();
  inputEnded = false;
}

} // namespace webvtt
