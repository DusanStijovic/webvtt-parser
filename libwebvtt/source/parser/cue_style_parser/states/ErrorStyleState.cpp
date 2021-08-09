#include "parser/cue_style_parser/states/ErrorStyleState.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{
    void ErrorStyleState::processState()
    {
        //TODO throw errow
        styleSheetParser.setEndParsing(true);
    }

} // namespace WebVTT
