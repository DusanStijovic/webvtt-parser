#ifndef LIBWEBVTT_ERROR_STYLE_STATE_H
#define LIBWEBVTT_ERROR_STYLE_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{
    class ErrorStyleState : public StyleState
    {
    public:
        ErrorStyleState(StyleSheetParser &styleSheetParser) : StyleState(styleSheetParser) {}
        virtual void processState() override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ERROR_STYLE_STATE_H
