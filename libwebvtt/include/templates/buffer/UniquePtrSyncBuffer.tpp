
#include <algorithm>

namespace WebVTT
{

  template <typename ptrElem>
  ptrElem *UniquePtrSyncBuffer<ptrElem>::sendDataType()
  {
    return (*this->readPosition).get();
  }
  template <typename ptrElem>
  void UniquePtrSyncBuffer<ptrElem>::acceptDataToBuffer(std::unique_ptr<ptrElem> &&elem)
  {
    this->buffer.push_back(std::move(elem));
  }
  template <typename ptrElem>
  ptrElem *UniquePtrSyncBuffer<ptrElem>::sendDataTypeNoValue()
  {
    return nullptr;
  }

  template <typename ptrElem>
  void UniquePtrSyncBuffer<ptrElem>::writeMultiple(std::list<std::unique_ptr<ptrElem>> &elements)
  {
    // std::lock_guard<std::mutex> lock(this->mutexWrite);
    // for (auto &elem : elements)
    // {
    //   this->buffer.push_back(std::move(elem));
    // }
    // elements.clear();
  }

  template <typename ptrElem>
  ptrElem *UniquePtrSyncBuffer<ptrElem>::getElemByID(std::u32string_view id)
  {
    std::lock_guard<std::mutex> lock(this->mutex);

    auto found = std::find_if(this->buffer.rbegin(),
                              this->buffer.rend(),
                              [&id](const std::unique_ptr<ptrElem> &elem)
                              {
                                return elem->getIdentifier() == id;
                              });
    if (found == this->buffer.rend())
      return nullptr;
    else
      return found->get();
  }
}