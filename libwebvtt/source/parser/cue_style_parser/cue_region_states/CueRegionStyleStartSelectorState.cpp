#include "parser/cue_style_parser/cue_region_states/StartCueRegionStyleSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/style_selectors/MatchAllSelector.hpp"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.hpp"

namespace webvtt
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

} // namespace webvtt
