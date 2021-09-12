#include "parser/cue_style_parser/selectorStates/StyleIdSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/style_selectors/IdSelector.hpp"

namespace webvtt {

void
StyleIdSelectorState::preprocessBuffer(StyleSheetParser &parser) {
  if (parser.getBuffer().empty())
    parser.setState(StyleState::StyleStateType::ERROR);

  bool error = false;
  if (!ParserUtil::checkIfCSSSIdentifierBeginningRightFormat(parser.getBuffer())) error = true;
  parser.getBuffer() = ParserUtil::convertCSSEscapedString(parser.getBuffer());

  if (error) {
    DILOGE("ID format not right");
    parser.setState(StyleState::StyleStateType::ERROR);
  }
}

std::unique_ptr <StyleSelector>
StyleIdSelectorState::makeNewStyleSelector(StyleSheetParser &parser) {
  auto help = std::make_unique<IdSelector>(parser.getBuffer());
  parser.getBuffer().clear();
  return help;
}

} // namespace webvtt
