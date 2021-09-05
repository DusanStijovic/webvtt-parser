
#include <algorithm>
#include <buffer/UniquePtrSyncBuffer.hpp>
#include "exceptions/NotImplementedError.hpp"

namespace webvtt {

template<typename ptrElem>
ptrElem *UniquePtrSyncBuffer<ptrElem>::sendDataType() {
  return (*this->readPosition).get();
}
template<typename ptrElem>
void UniquePtrSyncBuffer<ptrElem>::acceptDataToBuffer(std::unique_ptr<ptrElem> &&elem) {
  this->buffer.push_back(std::move(elem));
}
template<typename ptrElem>
ptrElem *UniquePtrSyncBuffer<ptrElem>::sendDataTypeNoValue() {
  return nullptr;
}

template<typename ptrElem>
bool UniquePtrSyncBuffer<ptrElem>::writeMultiple(std::list<std::unique_ptr<ptrElem>> &elements) {
  std::lock_guard<std::mutex> lock(this->mutexWrite);
  for (auto &elem : elements) {
    this->writeOne(std::move(elem));
  }
  elements.clear();
  return true;
}
template<typename ptrElem>
std::list<const ptrElem *> UniquePtrSyncBuffer<ptrElem>::readMultiple(uint32_t number) {
  std::lock_guard<std::mutex> lock(this->mutex);
  std::list<const ptrElem *> temp;
  for (uint32_t i = 0; i < number; i++) {
    temp.push_back(this->readOne());
  }
  return temp;
}

template<typename ptrElem>
ptrElem *UniquePtrSyncBuffer<ptrElem>::getElemByID(std::u32string_view id) {
  std::lock_guard<std::mutex> lock(this->mutex);

  auto found = std::find_if(this->buffer.rbegin(),
                            this->buffer.rend(),
                            [&id](const std::unique_ptr<ptrElem> &elem) {
                              return elem->getIdentifier() == id;
                            });
  if (found == this->buffer.rend())
    return nullptr;
  else
    return found->get();
}
template<typename ptrElem>
std::list<const ptrElem *> UniquePtrSyncBuffer<ptrElem>::readUntilSpecificData(const ptrElem &specificData) {
  throw NotImplementedError();
}

template<typename ptrElem>
std::list<const ptrElem *> UniquePtrSyncBuffer<ptrElem>::readWhileSpecificData(const ptrElem &specificData) {
  throw NotImplementedError();
}

}