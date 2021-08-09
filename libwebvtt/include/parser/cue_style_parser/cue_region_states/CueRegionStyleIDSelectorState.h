#ifndef LIBWEBVTT_CUE_REGION_ID_SELECTOR_STATE_H
#define LIBWEBVTT_CUE_REGION_ID_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleIDSelectorState.h"

namespace WebVTT
{
    class CueRegionStyleIDSelectorState : public StyleIDSelectorState
    {
        virtual void proceedToEndState() override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_CUE_REGION_ID_SELECTOR_STATE_H
