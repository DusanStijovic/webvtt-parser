#include "parser/cue_style_parser/selectorStates/StyleCollectPseudoClassArgument.hpp"
#include "parser/ParserUtil.hpp"
#include "parser/StyleSheetParser.hpp"
#include "../../../../include/parser/ParserUtil.hpp"

namespace webvtt {
void
StyleCollectPseudoArgument::processState(StyleSheetParser &parser) {
  uint32_t character = getNextCharacter();
  switch (character) {
    case ParserUtil::SOLIDUS_C:parser.saveStateBeforeComment();
      parser.setState(StyleState::StyleStateType::START_COMMENT_STATE);
      break;
    case ParserUtil::RIGHT_PARENTHESIS_C:parser.goToSavedPseudoState();
      break;
    default:parser.getAdditionalBuffer().push_back(character);
      break;
  }
}
} // namespace webvtt
