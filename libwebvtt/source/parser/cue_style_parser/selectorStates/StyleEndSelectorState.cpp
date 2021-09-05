#include "parser/cue_style_parser/selectorStates/StyleEndSelectorState.hpp"
#include "parser/ParserUtil.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt
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

} // namespace webvtt
