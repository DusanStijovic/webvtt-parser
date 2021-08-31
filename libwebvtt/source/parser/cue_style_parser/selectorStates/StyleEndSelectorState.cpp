#include "parser/cue_style_parser/selectorStates/StyleEndSelectorState.h"
#include "parser/ParserUtil.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{

    void StyleEndSelectorState::processState(StyleSheetParser &parser)
    {

        uint32_t character = getNextCharacter(parser);

        switch (character)
        {

        case ParserUtil::RIGHT_PARENTHESIS_C:
            parser.setState(StyleState::StyleStateType::BEFORE_RULE_STATE);
            break;

        default:
            parser.setState(StyleState::StyleStateType::ERROR);
        }
    }

} // namespace WebVTT
