#ifndef LIBWEBVTT_STYLE_ATTRIBUTE_SELECTOR_STATE_H
#define LIBWEBVTT_STYLE_ATTRIBUTE_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class StyleAttributeSelectorState : public StyleState
    {
        virtual void processState() override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_ATTRIBUTE_SELECTOR_STATE_H
