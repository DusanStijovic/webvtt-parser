#include "parser/cue_style_parser/states/ErrorStyleState.hpp"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt
{
    void ErrorStyleState::processState(StyleSheetParser &parser)
    {
        //TODO throw errow
        parser.setEndParsing(true);
        throw StyleSheetFormatError();
    }

} // namespace webvtt