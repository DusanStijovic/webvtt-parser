#ifndef LIBWEBVTT_STYLE_PSEUDO_CLASS_SELECTOR_STATE_H
#define LIBWEBVTT_STYLE_PSEUDO_CLASS_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{
    class StylePseudoClassSelectorState : public StyleState
    {
    public:
        virtual void processState() override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_PSEUDO_CLASS_SELECTOR_STATE_H
