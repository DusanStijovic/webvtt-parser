#ifndef LIBWEBVTT_END_SELECTOR_STATE_H
#define LIBWEBVTT_END_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class StyleEndSelectorState : public StyleState
    {
    public:
        virtual void processState() override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ENDSELECTORSTATE_H
