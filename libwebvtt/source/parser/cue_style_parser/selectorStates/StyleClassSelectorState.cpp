#include "parser/cue_style_parser/selectorStates/StyleClassSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/style_selectors/ClassSelector.hpp"

namespace webvtt
{

    void
    StyleClassSelectorState::preprocessBuffer(StyleSheetParser &parser)
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
    StyleClassSelectorState::makeNewStyleSelector(StyleSheetParser &parser)
    {
        auto help = std::make_unique<ClassSelector>(parser.getBuffer());
        parser.getBuffer().clear();
        return help;
    }

} // namespace webvtt