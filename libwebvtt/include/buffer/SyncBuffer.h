#ifndef SYNC_BUFFER_H
#define SYNC_BUFFER_H

#include <mutex>
#include <condition_variable>
#include <list>
#include <optional>

template<typename ContainerType, typename dataType>
class SyncBuffer {
public:
    SyncBuffer();

    /**
     * Write next data to buffer if input is not ended. If input is ended return false.
     * If one try to write others that wants to write will be blocked until it finish.
     *
     * @param x data to be written in buffer
     * @return true if data was written, otherwise false.
     */
    bool writeNext(dataType x);

    /**
     * Write multiple data to buffer if input is not ended. If input is ended return false.
     * If one try to write multiple data others that wants to write will be blocked until it finish.
     *
     * @param x data to be written in buffer
     * @return true if data were written, otherwise false.
     */
    bool writeMultiple(ContainerType input);

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
    std::optional<dataType> readNext();

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
     * Read data from buffer until specified data in input found, if input is not ended. If input is ended return false.
     * All data different from specified data is put in container, reached specified data are left in buffer.
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
     * Read data from buffer while specified data in input found, if input is not ended. If input is ended return false.
     * All data same as specified data is put in container, reached different data are left in buffer.
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
     * Peek data from buffer.
     * Data are left in buffer, iterator is not incremented
     * @return value from buffer pointed by current iterator.
     */
    std::optional<dataType> peekOne();

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
    bool setReadPosition(typename std::list<dataType>::iterator position);

    /**
     *
     * @return current iterator
     */
    typename std::list<dataType>::iterator getReadPosition();

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
     * Check if read done, return data pointed by current iterator and advance iterator if read not done.
     * @return data pointed by current iterator
     */
    std::optional<dataType> isReadDoneAndAdvancedIfNot();

    /**
     * Check if read is done. Block until are some data in buffer or input ended flag is set.
     * @return true if read done, false otherwise.
     */
    bool isReadDone();

    //TODO Add reset method to buffer so that buffer can be used again.

private:
    constexpr static int NUM_OF_SLOTS = 10;

    std::list<dataType> buffer;
    typename std::list<dataType>::iterator readPosition;

    std::condition_variable emptyCV;
    std::mutex mutex;

    std::mutex mutexWrite;
    std::mutex mutexRead;

    /**
     * Write one data to buffer. Multiple simultaneous calls not block each other.
     * @param x data to be written
     * @return true if data was written, false otherwise
     */
    bool writeOne(dataType x);

    /**
     * Read one data from buffer. Data are left in buffer, iterator is not incremented
     * @return read one data from buffer. If input ended return std::nullopt.
     */
    std::optional<dataType> readOne();

    bool inputEnded = false;

};
/**
 * Include sync buffer implementation
 */
#include "templates/buffer/SyncBuffer.tpp"
#endif