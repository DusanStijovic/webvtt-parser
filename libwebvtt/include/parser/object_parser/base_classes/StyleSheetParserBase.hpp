#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_STYLE_SHEET_PARSER_BASE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_STYLE_SHEET_PARSER_BASE_HPP_
#include "parser/object_parser/ObjectParser.hpp"
#include "elements/webvtt_objects/StyleSheet.hpp"

namespace webvtt{
class StyleSheetParserBase : public ObjectParser<StyleSheet> {
 public:
  inline std::list <std::unique_ptr<StyleSheet>> &getStyleSheets() { return styleSheets; }
 protected:
  std::list <std::unique_ptr<StyleSheet>> styleSheets;
};
} // namespace webvtt
#endif //LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_STYLE_SHEET_PARSER_BASE_HPP_
