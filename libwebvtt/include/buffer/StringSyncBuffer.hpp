#ifndef LIBWEBVTT_INCLUDE_BUFFER_STRING_SYNC_BUFFER_HPP_
#define LIBWEBVTT_INCLUDE_BUFFER_STRING_SYNC_BUFFER_HPP_

#include <mutex>
#include <condition_variable>
#include <list>
#include <optional>
#include "buffer/SyncBuffer.hpp"

namespace webvtt {
template<typename ContainerType, typename dataType>
class StringSyncBuffer : public SyncBuffer<
    dataType, dataType,
    dataType, std::optional<dataType>,
    ContainerType, ContainerType> {
 public:

  bool writeMultiple(ContainerType input) override;
  ContainerType readMultiple(uint32_t number) override;

  ContainerType readUntilSpecificData(dataType specificData) override;
  ContainerType readWhileSpecificData(dataType specificData) override;

 protected:
  std::optional<dataType> sendDataType() override;
  void acceptDataToBuffer(dataType) override;
  std::optional<dataType> sendDataTypeNoValue() override;
};

} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/StringSyncBuffer.tpp"

#endif // LIBWEBVTT_INCLUDE_BUFFER_STRING_SYNC_BUFFER_HPP_