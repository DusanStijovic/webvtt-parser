#include "parser/cue_style_parser/states/StyleIDSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_objects/IDSelector.h"

namespace WebVTT
{
    void StyleIDSelectorState::processState()
    {
        auto &currentPosition = styleSheetParser.getCurrentPosition();

        std::u32string_view result = ParserUtil::parseUntilCharacter(styleSheetParser.getInput(), ParserUtil::RIGHT_PARENTHESIS_C, currentPosition);

        if (currentPosition == styleSheetParser.getInput().end())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        currentPosition++;
        //TODO set seelctor to current object;
        styleSheetParser.setSelectorToCurrentObject(std::make_shared<IDSelector>(ParserUtil::convertCSSEscapedString(result)));
        styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::END_SELECTOR);
    }
} // namespace WebVTT
