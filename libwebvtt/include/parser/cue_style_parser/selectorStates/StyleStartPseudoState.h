#ifndef STYLE_START_PSEUDO_STATE_H
#define STYLE_START_PSEUDO_STATE_H

#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class StyleStartPseudoState : public StyleState
    {
    public:
        StyleStartPseudoState() = default;
        void processState(StyleSheetParser &parser) override;

    private:
    };
} // namespace WebVTT

#endif // STYLE_START_PSEUDO_STATE_H