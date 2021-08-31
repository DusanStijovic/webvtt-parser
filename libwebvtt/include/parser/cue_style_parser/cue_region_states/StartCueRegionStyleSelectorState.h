#ifndef LIBWEBVTT_START_CUE_REGION_STYLE_SELECTOR_STATE_H
#define LIBWEBVTT_START_CUE_REGION_STYLE_SELECTOR_STATE_H

#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{
    class StartCueRegionStyleSelectorState : public StyleState
    {
    public:
        StartCueRegionStyleSelectorState() = default;
        virtual void processState(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_START_CUE_REGION_STYLE_SELECTOR_STATE_H
