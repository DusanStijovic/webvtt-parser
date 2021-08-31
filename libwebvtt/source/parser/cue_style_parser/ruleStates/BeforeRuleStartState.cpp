#include "parser/cue_style_parser/ruleStates/BeforeRuleStartState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    void BeforeRuleStartState::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter(parser);

        if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
            return;

        switch (character)
        {
        case ParserUtil::COMMA_C:
        {
            parser.addCurrentObjectToStyleSheetList();
            parser.setState(StyleState::StyleStateType::START);
            break;
        }
        case ParserUtil::LEFT_CURLY_BRACKET_C:
            parser.setState(StyleState::StyleStateType::RULES);
            break;

        default:
            parser.setState(StyleState::StyleStateType::ERROR);
            break;
        }
    }

} // namespace WebVTT
