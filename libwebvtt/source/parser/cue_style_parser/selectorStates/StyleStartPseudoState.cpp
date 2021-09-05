#include "parser/cue_style_parser/selectorStates/StyleStartPseudoState.hpp"
#include "parser/ParserUtil.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt {

void StyleStartPseudoState::processState(StyleSheetParser &parser) {
  uint32_t character = getNextCharacter(parser);

  switch (character) {
    case ParserUtil::COLON_C:parser.setState(StyleState::StyleStateType::PSEUDO_ELEMENT_SELECTOR);
      break;

    default:parser.getBuffer().push_back(character);
      parser.setState(StyleState::StyleStateType::PSEUDO_CLASS_SELECTOR);
      break;
  }
}

} // namespace webvtt
