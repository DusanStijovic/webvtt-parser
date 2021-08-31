#include "parser/cue_style_parser/selectorStates/StyleClassSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_selectors/ClassSelector.h"

namespace WebVTT
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

} // namespace WebVTT