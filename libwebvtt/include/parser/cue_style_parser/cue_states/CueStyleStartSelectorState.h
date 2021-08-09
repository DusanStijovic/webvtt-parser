#ifndef LIBWEBVTT_STYLE_APPLY_MARKS_STATE_H
#define LIBWEBVTT_STYLE_APPLY_MARKS_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class CueStyleStartSelectorState : public StyleState
    {
    public:
        CueStyleStartSelectorState(StyleSheetParser &styleSheetParser) : StyleState(styleSheetParser) {}
        virtual void processState() override;
    };

}

#endif //LIBWEBVTT_STYLE_APPLY_MARKS_STATE_H
