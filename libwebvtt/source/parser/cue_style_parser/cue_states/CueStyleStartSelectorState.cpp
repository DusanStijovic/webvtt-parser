#include "parser/cue_style_parser/cue_states/CueStyleStartSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    void CueStyleStartSelectorState::processState(StyleSheetParser &parser)
    {

        uint32_t character = getNextCharacter(parser);

        if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
            return;

        switch (character)
        {

        case ParserUtil::HASHTAG_C:
            parser.setState(StyleState::StyleStateType::ID_SELECTOR);
            break;

        case ParserUtil::DOT_C:
            parser.setState(StyleState::StyleStateType::CLASS_SELECTOR);
            break;

        case ParserUtil::COLON_C:
            parser.setState(StyleState::StyleStateType::PSEUDO_START);
            break;
        case ParserUtil::LEFT_SQUARE_BRACKET_C:
            parser.setState(StyleState::StyleStateType::ATTRIBUTE_SELECTOR);
            break;
        case StyleSheetParser::STOP_PARSER:
            parser.setState(StyleState::StyleStateType::ERROR);
            break;

        default:
            parser.setState(StyleState::StyleStateType::TYPE_SELECTOR);
            parser.getBuffer().push_back(character);
            break;
        }
    }

} // namespace WebVTT
