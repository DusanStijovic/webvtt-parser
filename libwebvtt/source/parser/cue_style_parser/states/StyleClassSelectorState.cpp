#include "parser/cue_style_parser/states/StyleClassSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_objects/ClassSelector.h"

namespace WebVTT
{
    void StyleClassSelectorState::processState()
    {
        auto &currentPosition = styleSheetParser.getCurrentPosition();
        auto result = ParserUtil::parseUntilCharacter(styleSheetParser.getInput(), ParserUtil::RIGHT_PARENTHESIS_C, currentPosition);

        if (currentPosition == styleSheetParser.getInput().end())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        styleSheetParser.setSelectorToCurrentObject(std::make_shared<ClassSelector>(result));
        currentPosition++;
        styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::END_SELECTOR);
    }

} // namespace WebVTT