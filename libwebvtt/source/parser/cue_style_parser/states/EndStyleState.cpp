#include "parser/cue_style_parser/states/EndStyleState.hpp"
#include "parser/ParserUtil.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt {
void
EndStyleState::processState(StyleSheetParser &parser) {

  uint32_t character = getNextCharacter(parser);

  if (ParserUtil::SOLIDUS_C == character) {
    parser.saveStateBeforeComment();
    parser.setState(StyleState::StyleStateType::START_COMMENT_STATE);
    return;
  }
  if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
    return;

  if (character != StyleSheetParser::STOP_PARSER)
    parser.setState(StyleState::StyleStateType::ERROR);
  else
    parser.setEndParsing(true);
}

} // namespace webvtt
