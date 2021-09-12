
namespace webvtt {
template<typename OneElemType>
bool StringBuffer<OneElemType>::writeMultiple(const std::basic_string<OneElemType> &input) {
  bool success;
  for (auto one : input) {
    success = this->writeOne(one);
    if (!success)
      return false;
  }
  return true;
}
template<typename OneElemType>
std::basic_string<OneElemType> StringBuffer<OneElemType>::readMultiple(uint32_t number) {
  std::basic_string<OneElemType> values;
  for (uint32_t i = 0; i < number; i++) {
    auto result = this->readOne();
    if (result.has_value()) {
      values.push_back(result.value());
    } else
      return values;
  }
  return values;
}
template<typename OneElemType>
std::basic_string<OneElemType> StringBuffer<OneElemType>::readUntilSpecificData(const OneElemType &specificData) {
  std::basic_string<OneElemType> values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() != specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}
template<typename OneElemType>
std::basic_string<OneElemType> StringBuffer<OneElemType>::readWhileSpecificData(const OneElemType &specificData) {
  std::basic_string<OneElemType> values;

  auto result = this->peekOne();
  while (result.has_value() && result.value() == specificData) {
    result = this->readOne();
    values.push_back(result.value());
    result = this->peekOne();
  }
  return values;
}
template<typename OneElemType>
bool StringBuffer<OneElemType>::writeNext(const OneElemType &elem) {
  return this->writeOne(elem);
}
template<typename OneElemType>
std::optional<OneElemType> StringBuffer<OneElemType>::readNext() {
  return this->readOne();
}
template<typename OneElemType>
size_t StringBuffer<OneElemType>::getReadPosition() {
  return this->readPosition;
}
template<typename OneElemType>
bool StringBuffer<OneElemType>::setReadPosition(size_t position) {
  if (position > this->buffer.length()) return false;
  this->readPosition = position;
  return true;
}
template<typename OneElemType>
void StringBuffer<OneElemType>::clearBufferUntilReadPosition() {
  this->buffer.erase(this->buffer.begin(), this->buffer.begin() + this->readPosition);
  this->readPosition = 0;
}
template<typename OneElemType>
void StringBuffer<OneElemType>::resetBuffer() {
  this->buffer.clear();
  this->readPosition = 0;
  this->inputEnded = false;
}
template<typename OneElemType>
std::optional<OneElemType> StringBuffer<OneElemType>::isReadDoneAndAdvancedIfNot() {
  return readNext();
}
}