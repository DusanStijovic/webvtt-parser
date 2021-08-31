#include "parser/cue_style_parser/selectorStates/StylePseudoClassSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_selectors/PseudoClassSelector.h"

namespace WebVTT
{

    void
    StylePseudoClassSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character)
    {
        if (character == ParserUtil::LEFT_PARENTHESIS_C)
        {
            parser.setState(StyleState::StyleStateType::COLLECT_PSEUDO_ARGUMENT);
            parser.savePseudoState(StyleState::StyleStateType::PSEDO_CLASS_ARGUMENT_END);
        }
        else
        {
            FetchSelectorState::foundDefaultBehaviour(parser, character);
        }
    }

    void StylePseudoClassSelectorState::preprocessBuffer(StyleSheetParser &parser)
    {
        if (parser.getBuffer().empty())
            parser.setState(StyleState::StyleStateType::ERROR);
    }

    std::unique_ptr<StyleSelector> StylePseudoClassSelectorState::makeNewStyleSelector(StyleSheetParser &parser)
    {
        auto help = std::make_unique<PseudoClassSelector>(parser.getBuffer(), ParserUtil::EMPTY_STRING_VIEW);
        parser.getBuffer().clear();
        return help;
    }
} // namespace WebVTT
