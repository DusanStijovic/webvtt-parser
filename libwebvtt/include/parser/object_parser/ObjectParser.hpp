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
  /**
 * Set new object as parsing object
 *
 * @param newObject  new object to be set as parsing object
 * @return true if object set, otherwise false
 */
  virtual bool setNewObjectForParsing(std::unique_ptr<Object> newObject);

  // /**
  //  * Set new object as parsing object. Parser  make object by itself.
  //  * @return true if object set, otherwise false
  //  */
  // virtual bool setNewObjectForParsing();

  /**
 * @return return parser internal object and set internal object to nullptr
 */
  virtual std::unique_ptr<Object> collectCurrentObject();
};

} // namespace webvtt

#include "templates/parser/ObjectParser.tpp"

#endif // LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_OBJECT_PARSER_HPP_
