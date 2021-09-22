#include "parser/cue_style_parser/comment_states/StyleEndCommentState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt {

void StyleEndCommentState::processState(StyleSheetParser &parser) {

  uint32_t character = getNextCharacter(parser);
  switch (character) {
    case ParserUtil::SOLIDUS_C:parser.goToStateBeforeComment();
      break;
    default:parser.setState(StyleState::StyleStateType::COMMENT_STATE);
      break;
  };

}
} //namespace webvtt
