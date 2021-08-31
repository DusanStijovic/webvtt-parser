#include "parser/cue_style_parser/selectorStates/StyleStartPseudoState.h"
#include "parser/ParserUtil.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{

    void StyleStartPseudoState::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter(parser);

        switch (character)
        {
        case ParserUtil::COLON_C:
            parser.setState(StyleState::StyleStateType::PSEUDO_ELEMENT_SELECTOR);
            break;

        default:
            parser.setState(StyleState::StyleStateType::PSEUDO_CLASS_SELECTOR);
            break;
        }
    }

} // namespace WebVTT
