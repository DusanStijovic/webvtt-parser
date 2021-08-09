#include "parser/cue_style_parser/states/StyleRulesState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include <tuple>

namespace WebVTT
{
    void StyleRulesState::processState()
    {
        auto &currentPositioon = styleSheetParser.getCurrentPosition();
        auto &input = styleSheetParser.getInput();

        std::u32string_view help;
        std::u32string lookUpCharacters = {ParserUtil::LF_C, ParserUtil::RIGHT_CURLY_BRACKET_C};
        while (true)
        {
            help = ParserUtil::parseUntilAnyOfGivenCharacters(input, lookUpCharacters, currentPositioon);
            if (currentPositioon == input.end())
                break;

            ParserUtil::strip(help, ParserUtil::isWhiteSpaceCharacter);

            auto result = ParserUtil::splitStringAroundCharacter(help, ParserUtil::COLON_C);
            if (result.has_value())
            {
                auto name = std::get<0>(result.value());
                auto value = std::get<1>(result.value());
                ParserUtil::strip(name, ParserUtil::isWhiteSpaceCharacter);
                ParserUtil::strip(value, ParserUtil::isWhiteSpaceCharacter);
                processRule(name, value);
            }
            else
            {
                //TODO log error
            }

            if (*currentPositioon == ParserUtil::RIGHT_CURLY_BRACKET_C)
            {
                styleSheetParser.setEndParsing(true);
                return;
            }
            currentPositioon++;
        }
    }

} // namespace WebVTT
