#include "parser/cue_style_parser/states/StyleEndSelectorState.h"
#include "parser/ParserUtil.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{

    void StyleEndSelectorState::processState()
    {
        //TODO see if you alrready skip rigth parenthes

        //TODO see if you want to be able to put mutiple cue style definitions

        auto &currentPositioon = styleSheetParser.getCurrentPosition();
        auto &input = styleSheetParser.getInput();

        ParserUtil::skipWhiteSpaces(input, currentPositioon);

        if (currentPositioon == input.end() || *currentPositioon != ParserUtil::LEFT_CURLY_BRACKET_C)
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        currentPositioon++;
        styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::RULES);
    }

} // namespace WebVTT
