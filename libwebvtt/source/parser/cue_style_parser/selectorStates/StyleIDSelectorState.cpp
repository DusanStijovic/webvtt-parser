#include "parser/cue_style_parser/selectorStates/StyleIDSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/style_selectors/IDSelector.hpp"

namespace webvtt
{

  void
  StyleIDSelectorState::preprocessBuffer(StyleSheetParser &parser)
  {
    if (parser.getBuffer().empty())
      parser.setState(StyleState::StyleStateType::ERROR);
    parser.getBuffer() = ParserUtil::convertCSSEscapedString(parser.getBuffer());
    if (!ParserUtil::checkIfCSSSIdentifierRightFormat(parser.getBuffer()))
    {
      DILOGE("ID format not right");
      parser.setState(StyleState::StyleStateType::ERROR);
    }
  }

  std::unique_ptr<StyleSelector>
  StyleIDSelectorState::makeNewStyleSelector(StyleSheetParser &parser)
  {
    auto help = std::make_unique<IDSelector>(parser.getBuffer());
    parser.getBuffer().clear();
    return help;
  }

} // namespace webvtt
