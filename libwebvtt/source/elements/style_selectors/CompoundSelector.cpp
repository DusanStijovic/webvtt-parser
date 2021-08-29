#include "elements/style_objects/CompoundSelector.h"

namespace WebVTT
{
    StyleSelector::SelectorType
    CompoundSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::COMPOUND;
    }

    bool
    CompoundSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }

} // namespace WebVTT
