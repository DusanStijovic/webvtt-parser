#include "elements/style_objects/MatchAllSelector.h"

namespace WebVTT
{
    StyleSelector::SelectorType
    MatchAllSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::MATCH_ALL;
    }

    bool
    MatchAllSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }

} // namespace WebVTT
