#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_CUE_PARSER_BASE_H_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_CUE_PARSER_BASE_H_
#include "elements/webvtt_objects/Cue.hpp"
#include "parser/object_parser/ObjectParser.hpp"

namespace webvtt {

class CueParserBase : public ObjectParser<Cue> {
 public:
  virtual void setTextToObject(std::u32string text) = 0;

  virtual void parseTextStyleAndMakeStyleTree(std::u32string_view defaultLanguage = U"") = 0;
};
}

#endif //LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_CUE_PARSER_BASE_H_
