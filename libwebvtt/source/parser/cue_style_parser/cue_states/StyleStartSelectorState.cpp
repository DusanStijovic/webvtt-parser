#include "parser/cue_style_parser/cue_states/StyleStartSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt {

void StyleStartSelectorState::processState(StyleSheetParser &parser) {

  uint32_t character = getNextCharacter(parser);

  if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
    return;

  StyleState::StyleStateType newState = StyleState::StyleStateType::ERROR;
  StyleSelector::SelectorType selectorType = StyleSelector::SelectorType::UNSET;

  switch (character) {

    case ParserUtil::HASHTAG_C: newState = StyleState::StyleStateType::ID_SELECTOR;
      selectorType = StyleSelector::SelectorType::ID;
      break;

    case ParserUtil::DOT_C:newState = StyleState::StyleStateType::CLASS_SELECTOR;
      selectorType = StyleSelector::SelectorType::CLASS;
      break;

    case ParserUtil::COLON_C:DILOGE("PSEUDO ELEMENTS AND CLASSES NOT SUPPORTED");
      //throw NotImplementedError();
      newState = StyleState::StyleStateType::PSEUDO_START;
      selectorType = StyleSelector::SelectorType::PSEUDO_CLASS;
      break;
    case ParserUtil::LEFT_SQUARE_BRACKET_C:newState = StyleState::StyleStateType::ATTRIBUTE_SELECTOR;
      selectorType = StyleSelector::SelectorType::ATTRIBUTE;
      break;
    case StyleSheetParser::STOP_PARSER: newState = StyleState::StyleStateType::ERROR;
      break;
    default:newState = StyleState::StyleStateType::TYPE_SELECTOR;
      selectorType = StyleSelector::SelectorType::TYPE;
      parser.getBuffer().push_back(character);
      break;
  }
  if (parser.getCurrentParsedObject()->isSelectorAllowed(selectorType)) {
    parser.setState(newState);
  } else {
    DILOGE("Given Selector not supported for given stylesheet");
    parser.setState(StyleState::StyleStateType::ERROR);
  }
}

} // namespace webvtt
