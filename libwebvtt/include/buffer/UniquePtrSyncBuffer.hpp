#ifndef LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_HPP_
#include "buffer/SyncBuffer.hpp"
#include <memory>
#include <list>
namespace webvtt {

template<typename ptrElem>
class UniquePtrSyncBuffer : public SyncBuffer<
    std::unique_ptr<ptrElem>, const ptrElem &,
    std::unique_ptr<ptrElem> &&, const ptrElem *,
    std::list<std::unique_ptr<ptrElem>> &, std::list<const ptrElem *>
> {
 public:
  ptrElem *getElemByID(std::u32string_view id);
  bool writeMultiple(std::list<std::unique_ptr<ptrElem>> &input) override;
  std::list<const ptrElem *> readMultiple(uint32_t number) override;

  std::list<const ptrElem *> readUntilSpecificData(const ptrElem &specificData) override;
  std::list<const ptrElem *> readWhileSpecificData(const ptrElem &specificData) override;

 protected:
  ptrElem *sendDataType() override;
  void acceptDataToBuffer(std::unique_ptr<ptrElem> &&) override;
  ptrElem *sendDataTypeNoValue() override;
};

} // End of namespace webvtt
#include "templates/buffer/UniquePtrSyncBuffer.tpp"

#endif //LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_HPP_