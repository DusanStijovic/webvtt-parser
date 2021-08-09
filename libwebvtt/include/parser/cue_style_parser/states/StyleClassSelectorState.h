#ifndef LIB_WEBVTT_CLASS_SELECTOR_STATE_H
#define LIB_WEBVTT_CLASS_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class StyleClassSelectorState : public StyleState
    {
    public:
        virtual void processState() override;
    };

}

#endif //LIB_WEBVTT_CLASS_SELECTOR_STATE_H
