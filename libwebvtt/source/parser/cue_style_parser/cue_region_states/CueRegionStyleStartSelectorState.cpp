#include "parser/cue_style_parser/cue_region_states/StartCueRegionStyleSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_selectors/MatchAllSelector.h"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.h"

namespace WebVTT
{
    void StartCueRegionStyleSelectorState::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter(parser);

        if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
            return;

        switch (character)
        {
        case ParserUtil::HASHTAG_C:
            parser.setState(StyleState::StyleStateType::ID_SELECTOR);
            break;
        default:
            parser.setState(StyleState::StyleStateType::ERROR);
            break;
        }
    }

} // namespace WebVTT
