#include "parser/cue_style_parser/states/ErrorStyleState.hpp"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt {
void ErrorStyleState::processState(StyleSheetParser &parser) {
  throw StyleSheetFormatError();
}

} // namespace webvtt