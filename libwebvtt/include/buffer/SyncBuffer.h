#ifndef LIBWEBVTT_INCLUDE_BUFFER_SYNC_BUFFER_H_
#define LIBWEBVTT_INCLUDE_BUFFER_SYNC_BUFFER_H_

#include <mutex>
#include <condition_variable>
#include <list>
#include <optional>

namespace WebVTT
{
    template <typename StoredDataType, typename ReceivedDataType, typename SendDataType>
    class SyncBuffer
    {
    public:
        SyncBuffer();

        SyncBuffer(const SyncBuffer &) = delete;
        SyncBuffer(SyncBuffer &&) = delete;
        SyncBuffer &operator=(const SyncBuffer &) = delete;
        SyncBuffer &operator=(SyncBuffer &&) = delete;

        /**
* Write next data to buffer if input is not ended. If input is ended return false.
* If one try to write others that wants to write will be blocked until it finish.
*
* @param x data to be written in buffer
* @return true if data was written, otherwise false.
*/
        bool writeNext(ReceivedDataType x);

        /**
* Read data from buffer if input is not ended. If input is ended return false.
* If one try to read multiple others will be blocked until it finish.
* If there is not data in buffer and input not ended then caller will be blocked until
* data appear or input ended.
*
* Data are left in buffer, only current iterator is increment.
*
* @return read data or std::nullopt if input ended read.
*/
        SendDataType readNext();

        /**
* Remove all elements in buffer until current iterator.
*/
        void clearBufferUntilReadPosition();

        /**
* Set current iterator to given position
* If iterator is equal end iterator, iterator is not set.
*
* @param position  new current iterator
* @return true if current iterator set, false otherwise
*/
        bool setReadPosition(typename std::list<StoredDataType>::iterator position);

        /**
*
* @return current iterator
*/
        typename std::list<StoredDataType>::iterator getReadPosition();

        /**
*
* @return if input ended flag is set
*/
        bool isInputEnded();

        /**
*
* Set input ended flag to true
*/
        void setInputEnded();

        /**
* Check if read is done. Block until are some data in buffer or input ended flag is set.
* @return true if read done, false otherwise.
*/
        bool isReadDone();

        //TODO Add reset method to buffer so that buffer can be used again.

        SendDataType peekOne();
        /**
* Write one data to buffer. Multiple simultaneous calls not block each other.
* @param x data to be written
* @return true if data was written, false otherwise
*/
        bool writeOne(ReceivedDataType x);

    protected:
        std::list<StoredDataType> buffer;
        typename std::list<StoredDataType>::iterator readPosition;

        std::condition_variable emptyCV;

        std::mutex mutex;

        std::mutex mutexWrite;
        std::mutex mutexRead;

        virtual void acceptDataToBuffer(ReceivedDataType x) = 0;

        virtual SendDataType sendDataType() = 0;

        virtual SendDataType sendDataTypeNoValue() = 0;

        /**
* Read one data from buffer. Data are left in buffer, iterator is not incremented
* @return read one data from buffer. If input ended return std::nullopt.
*/
        SendDataType readOne();

        bool inputEnded = false;
    };

} // end of namespace
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/SyncBuffer.tpp"
#endif //LIBWEBVTT_INCLUDE_BUFFER_SYNC_BUFFER_H_
