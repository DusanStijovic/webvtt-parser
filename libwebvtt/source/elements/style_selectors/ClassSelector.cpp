#include "elements/style_selectors/ClassSelector.h"

namespace WebVTT
{
    StyleSelector::SelectorType
    ClassSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::CLASS;
    }

    bool
    ClassSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }

} // namespace WebVTT
