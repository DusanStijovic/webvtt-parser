#include "parser/cue_style_parser/selectorStates/StylePseudoElementSelectorState.hpp"
#include "elements/style_selectors/pseudo_element_selectors/PseudoElementSelector.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt {
void StylePseudoElementSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) {
  if (character == ParserUtil::LEFT_PARENTHESIS_C) {
    parser.setState(StyleState::StyleStateType::COLLECT_PSEUDO_ARGUMENT);
    parser.savePseudoState(StyleState::StyleStateType::PSEUDO_ELEMENT_ARGUMENT_END);
  } else {
    FetchSelectorState::foundDefaultBehaviour(parser, character);
  }
};

void StylePseudoElementSelectorState::preprocessBuffer(StyleSheetParser &parser) {
  if (parser.getBuffer().empty())
    parser.setState(StyleState::StyleStateType::ERROR);
};

std::unique_ptr<StyleSelector> StylePseudoElementSelectorState::makeNewStyleSelector(StyleSheetParser &parser) {

  auto help = PseudoElementSelector::makeNewPseudoElementSelector(parser.getBuffer());
  parser.getBuffer().clear();
  return help;
};
} // namespace webvtt
