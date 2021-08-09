#ifndef LIBWEBVTT_ID_SELECTOR_STATE_H
#define LIBWEBVTT_ID_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class StyleIDSelectorState : public StyleState
    {
    public:
        virtual void processState() override;
        virtual void proceedToEndState() = 0;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_IDSELECTORSTATE_H
