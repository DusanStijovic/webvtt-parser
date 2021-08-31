#ifndef BEFORE_RULE_STATE_H
#define BEFORE_RULE_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{

    class BeforeRuleStartState : public StyleState
    {
    public:
        BeforeRuleStartState() = default;
        virtual void processState(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif //BEFORE_RULE_STATE_H