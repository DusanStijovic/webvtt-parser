#ifndef END_STYLE_STATE_H
#define END_STYLE_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{
    class EndStyleState : public StyleState
    {
    public:
        EndStyleState() = default;
        virtual void processState(StyleSheetParser &parser) override;
    };
} // namespace WebVTT

#endif // END_STYLE_STATE_H