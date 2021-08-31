#include "parser/cue_style_parser/states/ErrorStyleState.h"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{
    void ErrorStyleState::processState(StyleSheetParser &parser)
    {
        //TODO throw errow
        parser.setEndParsing(true);
        throw StyleSheetFormatError();
    }

} // namespace WebVTT