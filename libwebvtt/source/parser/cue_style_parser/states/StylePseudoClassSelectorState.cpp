#include "parser/cue_style_parser/states/StylePseudoClassSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_objects/AttributeSelector.h"

namespace WebVTT
{
    void StylePseudoClassSelectorState::processState()
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
        case ParserUtil::LEFT_PARENTHESIS_C:
        {
            currentPositioon++;
            if (styleSheetParser.getTypeMark() != ParserUtil::LANG_TYPE_MARK)
            {
                styleSheetParser.setEndParsing(true);
                return;
            }
            auto language = ParserUtil::parseUntilCharacter(input, ParserUtil::RIGHT_PARENTHESIS_C, currentPositioon);
            if (currentPositioon == input.end())
            {
                styleSheetParser.setEndParsing(true);
                return;
            }
            currentPositioon++;
            if (currentPositioon == input.end() || *currentPositioon != ParserUtil::RIGHT_PARENTHESIS_C)
            {
                styleSheetParser.setEndParsing(true);
                return;
            }
            styleSheetParser.setSelectorToCurrentObject(std::make_shared<AttributeSelector>(styleSheetParser.getTypeMark(), language));
            break;
        }
        case ParserUtil::RIGHT_PARENTHESIS_C:
        {
            auto result = styleSheetParser.getTypeMark();
            if (result != U"past" && result != U"future")
            {
                styleSheetParser.setEndParsing(true);
                return;
            }
            //TODO Make future/past selector
            break;
        }
        default:
            styleSheetParser.getTypeMark().push_back(*currentPositioon);
            break;
        }
    }

} // namespace WebVTT
