#include "parser/cue_style_parser/selectorStates/StylePseudoClassSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/style_selectors/pseudo_class_selectors/PseudoClassSelector.hpp"
#include "utf8.h"

namespace webvtt {

void
StylePseudoClassSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) {
  if (character == ParserUtil::LEFT_PARENTHESIS_C) {
    parser.setState(StyleState::StyleStateType::COLLECT_PSEUDO_ARGUMENT);
    parser.savePseudoState(StyleState::StyleStateType::PSEDO_CLASS_ARGUMENT_END);
  } else {
    FetchSelectorState::foundDefaultBehaviour(parser, character);
  }
}

void StylePseudoClassSelectorState::preprocessBuffer(StyleSheetParser &parser) {
  if (parser.getBuffer().empty())
    parser.setState(StyleState::StyleStateType::ERROR);
}

std::unique_ptr<StyleSelector> StylePseudoClassSelectorState::makeNewStyleSelector(StyleSheetParser &parser) {
  auto help = PseudoClassSelector::makeNewPseudoClassSelector(parser.getBuffer());

  parser.getBuffer().clear();
  return help;
}
} // namespace webvtt
