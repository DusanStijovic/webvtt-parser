#include <parser/ParserUtil.hpp>
#include "parser/cue_style_parser/comment_states/StyleStartCommentState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt {

void StyleStartCommentState::processState(StyleSheetParser &parser) {

  uint32_t character = getNextCharacter(parser);

  switch (character) {
    case ParserUtil::ASTERIX_C:parser.setState(StyleState::StyleStateType::COMMENT_STATE);
      break;
    default:parser.getBuffer().push_back(ParserUtil::SOLIDUS_C);
      parser.goToStateBeforeComment();
      break;
  }

};

}

