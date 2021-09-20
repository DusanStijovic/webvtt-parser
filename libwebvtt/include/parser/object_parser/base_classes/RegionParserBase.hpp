#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_REGION_PARSER_BASE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_REGION_PARSER_BASE_HPP_
#include "parser/object_parser/ObjectParser.hpp"
#include "elements/webvtt_objects/Region.hpp"

namespace webvtt {

class RegionParserBase : public ObjectParser<Region> {

};

} // namespace webvtt

#endif //LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_BASE_CLASSES_REGION_PARSER_BASE_HPP_
