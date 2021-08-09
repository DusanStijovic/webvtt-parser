#include "parser/cue_style_parser/states/StyleStartState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/RegionStyleSheet.h"
#include "elements/CueStyleSheet.h"

namespace WebVTT
{

    bool StyleStartState::checkIfInputStartWith(std::u32string_view string)
    {
        auto size = styleSheetParser.getInput().end() - styleSheetParser.getCurrentPosition();
        if (size < string.length())
        {
            return false;
        }

        std::u32string_view begin = ParserUtil::make_string_view_from_iterators(styleSheetParser.getInput(), styleSheetParser.getCurrentPosition(),
                                                                                styleSheetParser.getCurrentPosition() + string.length());

        if (StyleSheetParser::CUE_STYLE_START != begin)
        {
            return false;
        }
        return true;
    }

    void StyleStartState::processState()
    {
        ParserUtil::skipWhiteSpaces(styleSheetParser.getInput(), styleSheetParser.getCurrentPosition());
        bool success = checkIfInputStartWith(StyleSheetParser::CUE_STYLE_START);
        if (!success)
        {
            styleSheetParser.setEndParsing(true);
            return;
        }
        styleSheetParser.getCurrentPosition() += StyleSheetParser::CUE_STYLE_START.length();

        if (styleSheetParser.getCurrentPosition() == styleSheetParser.getInput().end())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }

        if (*styleSheetParser.getCurrentPosition() == ParserUtil::HYPHEN_MINUS)
        {

            styleSheetParser.getCurrentPosition()++;
            success = checkIfInputStartWith(StyleSheetParser::REGION_STYLE_START);
            if (!success)
            {
                styleSheetParser.setEndParsing(true);
                return;
            }
            styleSheetParser.getCurrentPosition() += StyleSheetParser::REGION_STYLE_START.length();
            styleSheetParser.setNewObjectForParsing(std::make_shared<RegionStyleSheet>());
        }
        else
        {
            styleSheetParser.setNewObjectForParsing(std::make_shared<CueStyleSheet>());
        }

        if (styleSheetParser.getCurrentPosition() == styleSheetParser.getInput().end() || ParserUtil::LEFT_PARENTHESIS_C !=
                                                                                              *styleSheetParser.getCurrentPosition())
        {
            styleSheetParser.setEndParsing(true);
            return;
        }

        styleSheetParser.setState(StyleSheetParser::StyleSheetParserState::START_SELECTOR);
    }
}