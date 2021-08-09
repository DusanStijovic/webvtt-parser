#include "parser/cue_style_parser/states/StyleAttributeSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_objects/AttributeSelector.h"
#include <tuple>

namespace WebVTT
{

    void StyleAttributeSelectorState::processState()
    {
        auto &currentPositioon = styleSheetParser.getCurrentPosition();
        auto &input = styleSheetParser.getInput();

        auto result = ParserUtil::parseUntilCharacter(input, ParserUtil::RIGHT_SQUARE_BRACKET, currentPositioon);

        if (currentPositioon == input.end())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        currentPositioon++;
        ParserUtil::skipWhiteSpaces(input, currentPositioon);
        if (currentPositioon == input.end() || currentPositioon != ParserUtil::LEFT_PARENTHESIS)
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        auto &typeName = styleSheetParser.getTypeMark();
        auto split = ParserUtil::splitStringAroundCharacter(ParserUtil::EQUAL_C);
        if (!split.has_value())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        auto &attributeName = std::get<0>(split.value());
        auto &attrbuteValue = std::get<1>(split.value());

        ParserUtil::strip(attributeName, ParserUtil::isWhiteSpaceCharacter);
        ParserUtil::strip(attributeValue, ParserUtil::isWhiteSpaceCharacter);

        bool isOk = false;

        if (typeName == ParserUtil::VOICE_TYPE_MARK && attributeName == ParserUtil::VOICE_ATRIBUTE_MARK)
        {
            isOk = true;
        }
        if (typeName == ParserUtil::LANG_TYPE_MARK && attributeName == ParserUtil::LANG_ATTRIBUTE_MARK)
        {
            isOk = true;
        }
        if (typeName.empty() && attributeName == ParserUtil::LANG_ATTRIBUTE_MARK)
        {
            isOk = true;
        }

        if (isOk)
        {
            styleSheetParser.setSelectorToCurrentObject(std::make_shared<AttributeSelector>(attributeName, attributeValue));
            styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::END_SELECTOR);
            return;
        }
        else
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
    }
} // namespace WebVTT
