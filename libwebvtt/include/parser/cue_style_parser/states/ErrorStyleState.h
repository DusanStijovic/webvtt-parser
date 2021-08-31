#ifndef LIBWEBVTT_ERROR_STYLE_STATE_H
#define LIBWEBVTT_ERROR_STYLE_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{
    class ErrorStyleState : public StyleState
    {
    public:
        ErrorStyleState() = default;
        virtual void processState(StyleSheetParser & parser) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ERROR_STYLE_STATE_H