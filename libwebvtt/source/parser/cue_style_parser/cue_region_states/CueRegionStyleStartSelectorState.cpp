#include "parser/cue_style_parser/cue_region_states/StartCueRegionStyleSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_objects/MatchAllSelector.h"

namespace WebVTT
{
    void StartCueRegionStyleSelectorState::processState()
    {
        auto &currentPosition = styleSheetParser.getCurrentPosition();
        if (currentPosition == styleSheetParser.getInput().end())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        ParserUtil::skipWhiteSpaces(styleSheetParser.getInput(), currentPosition);

        if (*currentPosition == ParserUtil::HASHTAG_C)
        {
            currentPosition++;
            styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::CUE_REGION_ID_SELECTOR);
            return;
        }
        if (*currentPosition == ParserUtil::RIGHT_PARENTHESIS_C)
        {
            currentPosition++;
            styleSheetParser.setSelectorToCurrentObject(std::make_shared<MatchAllSelector>());
            styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::END_SELECTOR);
            return;
        }

        styleSheetParser.setEndParsing(true);
        return;
    }

} // namespace WebVTT
