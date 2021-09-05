#include "parser/cue_style_parser/selectorStates/StyleTypeSelectorState.hpp"
#include "elements/style_selectors/type_selectors/TypeSelector.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "parser/CSSConstants.hpp"

namespace webvtt {

bool StyleTypeSelectorState::checkIfTypeAllowed(std::u32string_view typeName) {
  if (typeName == CSSConstants::BOLD_TYPE)
    return true;
  if (typeName == CSSConstants::ITALIC_TYPE)
    return true;
  if (typeName == CSSConstants::CLASS_TYPE)
    return true;
  if (typeName == CSSConstants::LANG_TYPE)
    return true;
  if (typeName == CSSConstants::UNDERLINE_TYPE)
    return true;
  if (typeName == CSSConstants::VOICE_TYPE)
    return true;
  if (typeName == CSSConstants::RUBY_TYPE)
    return true;
  if (typeName == CSSConstants::RUBY_TEXT_TYPE)
    return true;
  return false;
}

void
StyleTypeSelectorState::preprocessBuffer(StyleSheetParser &parser) {
  if (parser.getBuffer().empty())
    parser.setState(StyleState::StyleStateType::ERROR);

  if (!checkIfTypeAllowed(std::u32string_view()))
    parser.setState(StyleState::StyleStateType::ERROR);
}

std::unique_ptr<StyleSelector>
StyleTypeSelectorState::makeNewStyleSelector(StyleSheetParser &parser) {
  auto help = TypeSelector::makeNewTypeSelector(parser.getBuffer());
  parser.getBuffer().clear();
  return help;
}

void StyleTypeSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) {
  if (character == ParserUtil::LEFT_SQUARE_BRACKET_C) {
    parser.setState(StyleState::StyleStateType::ATTRIBUTE_SELECTOR);
  } else {
    FetchSelectorState::foundDefaultBehaviour(parser, character);
  }
}

} // namespace webvtt
