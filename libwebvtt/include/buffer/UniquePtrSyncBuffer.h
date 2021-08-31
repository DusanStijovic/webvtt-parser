#ifndef LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_H_
#define LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_H_
#include "buffer/SyncBuffer.h"
#include <memory>
namespace WebVTT
{

  template <typename ptrElem>
  class UniquePtrSyncBuffer : public SyncBuffer<std::unique_ptr<ptrElem>, std::unique_ptr<ptrElem> &&, ptrElem *>
  {

  public:
    ptrElem *getElemByID(std::u32string_view id);
    void writeMultiple(std::list<std::unique_ptr<ptrElem>> &elements);

  protected:
    ptrElem *sendDataType() override;
    void acceptDataToBuffer(std::unique_ptr<ptrElem> &&) override;
    ptrElem *sendDataTypeNoValue() override;
  };

} // End of namespace WebVTT
#include "templates/buffer/UniquePtrSyncBuffer.tpp"
#endif //LIBWEBVTT_INCLUDE_BUFFER_UNIQUE_PTR_SYNC_BUFFER_H_
