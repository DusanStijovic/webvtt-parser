#ifndef LIBWEBVTT_MATCH_ALL_SELECTOR_H
#define LIBWEBVTT_MATCH_ALL_SELECTOR_H
#include "elements/style_objects/StyleSelector.h"
#include "elements/rules_filter_objects/RuleFilter.h"

namespace WebVTT
{
    class MatchAllSelector : public StyleSelector
    {
    public:
        MatchAllSelector() : StyleSelector() {}

        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;
    };
} // namespace WebVTT

#endif //LIBWEBVTT_MATCH_ALL_SELECTOR_H
