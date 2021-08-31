#ifndef LIBWEBVTT_STYLE_APPLY_MARKS_STATE_H
#define LIBWEBVTT_STYLE_APPLY_MARKS_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class CueStyleStartSelectorState : public StyleState
    {
    public:
        CueStyleStartSelectorState() = default;
        virtual void processState(StyleSheetParser &parser) override;
    };

}

#endif //LIBWEBVTT_STYLE_APPLY_MARKS_STATE_H
