#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_OBJECT_PARSER_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_OBJECT_PARSER_HPP_

#include <memory>

namespace webvtt {
/**
* Helper class for creating parser for specific webvtt object
* Object parser has one internal object in which will be set all parsed info
*
* @tparam Object some subtype of Block.
*/
template<typename Object>
class ObjectParser {
 protected:
  std::unique_ptr<Object> currentObject;

 public:
  ObjectParser() = default;
  ObjectParser(const ObjectParser &) = delete;
  ObjectParser(ObjectParser &&) = delete;
  ObjectParser &operator=(const ObjectParser &) = delete;
  ObjectParser &operator=(ObjectParser &&) = delete;
  virtual ~ObjectParser() = 0;

  virtual bool setNewObjectForParsing(std::unique_ptr<Object> newObject);

  virtual std::unique_ptr<Object> collectCurrentObject();
  const Object* getCurrentParsedObject();

  virtual void buildObjectFromString(std::u32string_view) = 0;
};

} // namespace webvtt

#include "templates/parser/ObjectParser.tpp"

#endif // LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_OBJECT_PARSER_HPP_
