#include "elements/style_selectors/PseudoElementSelector.h"

namespace WebVTT
{
    StyleSelector::SelectorType
    PseudoElementSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::PSEUDO_ELEMENT;
    }

    bool
    PseudoElementSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }

} // namespace WebVTT
