#include "parser/cue_style_parser/ruleStates/BeforeRuleStartState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt {

void BeforeRuleStartState::processState(StyleSheetParser &parser) {
  uint32_t character = getNextCharacter(parser);

  if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
    return;

  switch (character) {
    case ParserUtil::SOLIDUS_C:parser.saveStateBeforeComment();
      parser.setState(StyleState::StyleStateType::START_COMMENT_STATE);
      break;
    case ParserUtil::COMMA_C: {
      parser.setState(StyleState::StyleStateType::START);
      break;
    }
    case ParserUtil::LEFT_CURLY_BRACKET_C:parser.setState(StyleState::StyleStateType::RULES);
      break;

    default:parser.setState(StyleState::StyleStateType::ERROR);
      break;
  }
}

} // namespace webvtt
