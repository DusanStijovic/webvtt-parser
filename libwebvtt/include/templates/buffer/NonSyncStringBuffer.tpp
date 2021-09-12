

namespace webvtt {
template<typename OneElemType>
bool NonSyncStringBuffer<OneElemType>::isInputEnded() {
  return this->inputEnded;
}
template<typename OneElemType>
void NonSyncStringBuffer<OneElemType>::setInputEnded() {
  this->inputEnded = true;
}

template<typename OneElemType>
std::optional <OneElemType> NonSyncStringBuffer<OneElemType>::peekOne() {

  if (this->readPosition == this->buffer.length())
    return std::nullopt;

  return this->buffer[this->readPosition];
}
template<typename OneElemType>
bool NonSyncStringBuffer<OneElemType>::writeOne(const OneElemType &elem) {
  try {
    if (this->inputEnded)
      return false;

    this->buffer.push_back(elem);

    return true;
  }
  catch (const std::bad_alloc &error) {
    DILOGE(error.what());
    this->setInputEnded();
    throw;
  }
}
template<typename OneElemType>
std::optional <OneElemType> NonSyncStringBuffer<OneElemType>::readOne() {

  if (this->readPosition == this->buffer.length())
    return std::nullopt;

  return this->buffer[this->readPosition++];

}
template<typename OneElemType>
bool NonSyncStringBuffer<OneElemType>::isReadDone() {
  return this->readPosition == this->buffer.end() && this->inputEnded;
}
}