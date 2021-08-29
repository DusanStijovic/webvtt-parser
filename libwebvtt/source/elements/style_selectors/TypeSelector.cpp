#include "elements/style_objects/TypeSelector.h"

namespace WebVTT
{
    StyleSelector::SelectorType
    TypeSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::TYPE;
    }

    bool
    TypeSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }
} // namespace WebVTT
