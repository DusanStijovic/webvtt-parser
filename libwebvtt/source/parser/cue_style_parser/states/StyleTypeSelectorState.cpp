#include "parser/cue_style_parser/states/StyleTypeSelectorState.h"
#include "elements/style_objects/TypeSelector.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{
    void StyleTypeSelectorState::processState()
    {
        auto &currentPositioon = styleSheetParser.getCurrentPosition();
        auto &input = styleSheetParser.getInput();

        if (currentPositioon == input.end())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        switch (*currentPositioon)
        {
        case ParserUtil::RIGHT_PARENTHESIS_C:
            styleSheetParser.setSelectorToCurrentObject(std::make_shared<TypeSelector>(styleSheetParser.getTypeMark()));
            styleSheetParser.setEndParsing(true);
            styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::END_SELECTOR);
            break;

        case ParserUtil::LEFT_SQUARE_BRACKET_C:
            styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::ATTRIBUTE_SELECTOR);
            break;
        default:

            styleSheetParser.getTypeMark().push_back(*currentPositioon);
            break;
        }
        currentPositioon++;
    }

} // namespace WebVTT
