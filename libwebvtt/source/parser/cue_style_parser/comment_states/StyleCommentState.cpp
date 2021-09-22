#include "parser/cue_style_parser/comment_states/StyleCommentState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt {

void StyleCommentState::processState(StyleSheetParser &parser) {

  uint32_t character = getNextCharacter(parser);
  switch (character) {
    case ParserUtil::ASTERIX_C:parser.setState(StyleState::StyleStateType::END_COMMENT_STATE);
      break;
    default:
      // Ignore character
      break;
  }
}
}
