#include "elements/style_selectors/PseudoClassSelector.h"

namespace WebVTT
{

    StyleSelector::SelectorType
    PseudoClassSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::PSEUDO_CLASS;
    }

    bool
    PseudoClassSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }
} // namespace WebVTT
