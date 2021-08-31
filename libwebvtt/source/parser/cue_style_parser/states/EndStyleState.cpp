#include "parser/cue_style_parser/states/EndStyleState.h"
#include "parser/ParserUtil.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{
    void
    EndStyleState::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter(parser);
        if (ParserUtil::isASCIIWhiteSpaceCharacter(character))
            return;

        if (character != StyleSheetParser::STOP_PARSER)
            parser.setState(StyleState::StyleStateType::ERROR);
        else
            parser.setEndParsing(true);
    }

} // namespace WebVTT
