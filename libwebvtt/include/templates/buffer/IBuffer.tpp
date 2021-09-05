namespace webvtt {

template<typename StoredDataType, typename dataTypeToCompare, typename ReceivedDataType, typename SendDataType, typename ReceivedMultipleType, typename SendMultipleType>
IBuffer<StoredDataType,
        dataTypeToCompare,
        ReceivedDataType,
        SendDataType,
        ReceivedMultipleType,
        SendMultipleType>::IBuffer() {
  this->readPosition = this->buffer.begin();
}

} // namespace webvtt