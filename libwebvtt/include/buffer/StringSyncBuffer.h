#ifndef STRING_SYNC_BUFFER_H
#define STRING_SYNC_BUFFER_H

#include <mutex>
#include <condition_variable>
#include <list>
#include <optional>
#include "buffer/SyncBuffer.h"

namespace WebVTT
{
  template <typename ContainerType, typename dataType>
  class StringSyncBuffer : public SyncBuffer<dataType, dataType, std::optional<dataType>>
  {
  public:


    /**
* Write multiple data to buffer if input is not ended. If input is ended return false.
* If one try to write multiple data others that wants to write will be blocked until it finish.
*
* @param x data to be written in buffer
* @return true if data were written, otherwise false.
*/
    bool writeMultiple(ContainerType input);



    /**
* Read multiple data from buffer if input is not ended. If input is ended return false.
* If one try to read multiple others will be blocked until it finish.
* If there is not data in buffer and input not ended then caller will be blocked until
* data appear or input ended.
*
* Data are left in buffer, only current iterator is increment.
*
* @return read data in container or empty container if input ended.
*/
    ContainerType readMultiple(uint32_t number);

    /**
* Read data from buffer until specified data in input found, if input is not ended. If input is ended return empty container.
* All data different from specified data is put in container, reached different data is not put in container.
* If one try to read multiple others will be blocked until it finish.
* If there is not data in buffer and input not ended then caller will be blocked until
* data appear or input ended.
*
* Data are left in buffer, only current iterator is increment.
*
* @return read data in container or empty container if input ended.
*/
    ContainerType readUntilSpecificData(dataType specificData);

    /**
* Read data from buffer while specified data in input found, if input is not ended. If input is ended return empty container.
* All data same as specified data is put in container, reached different data is not put in container.
* If one try to read multiple others will be blocked until it finish.
* If there is not data in buffer and input not ended then caller will be blocked until
* data appear or input ended.
*
* Data are left in buffer, only iterator is increment.
*
* @return read data in container or empty container if input ended.
*/
    ContainerType readWhileSpecificData(dataType specificData);

    /**
* Check if read done, return data pointed by current iterator and advance iterator if read not done.
* @return data pointed by current iterator
*/
    std::optional<dataType> isReadDoneAndAdvancedIfNot();

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

#endif