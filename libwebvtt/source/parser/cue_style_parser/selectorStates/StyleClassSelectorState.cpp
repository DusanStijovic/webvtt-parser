#include "parser/cue_style_parser/selectorStates/StyleClassSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/style_selectors/ClassSelector.hpp"

namespace webvtt {

void
StyleClassSelectorState::preprocessBuffer(StyleSheetParser &parser) {
  if (parser.getBuffer().empty())
    parser.setState(StyleState::StyleStateType::ERROR);

  bool error = false;
  if (!ParserUtil::checkIfCSSSIdentifierBeginningRightFormat(parser.getBuffer())) error = true;
  parser.getBuffer() = ParserUtil::convertCSSEscapedString(parser.getBuffer());

  if (error) {
    DILOGE("class name format not right");
    parser.setState(StyleState::StyleStateType::ERROR);
  }
}

std::unique_ptr <StyleSelector>
StyleClassSelectorState::makeNewStyleSelector(StyleSheetParser &parser) {
  auto help = std::make_unique<ClassSelector>(parser.getBuffer());
  parser.getBuffer().clear();
  return help;
}

} // namespace webvtt