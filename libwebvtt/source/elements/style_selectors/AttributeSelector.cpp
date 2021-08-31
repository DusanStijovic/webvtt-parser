#include "elements/style_selectors/AttributeSelector.h"

namespace WebVTT
{
    void AttributeSelector::setStringMatchingType(StringMatchType stringMatchType)
    {
        this->stringMatchType = stringMatchType;
    }

    StyleSelector::SelectorType
    AttributeSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::ATTRIBUTE;
    }

    bool
    AttributeSelector::shouldApply(const NodeObject &node, const Cue &cue) const
    {
        return false;
    }
} // namespace WebVTT
