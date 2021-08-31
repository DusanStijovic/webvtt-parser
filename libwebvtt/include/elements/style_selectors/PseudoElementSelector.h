#ifndef PSEUDO_ELEMENT_SELECTOR_H
#define PSEUDO_ELEMENT_SELECTOR_H

#include "elements/style_selectors/StyleSelector.h"
#include <map>

namespace WebVTT
{
    class PseudoElementSelector : public StyleSelector
    {
    public:
        PseudoElementSelector(std::u32string_view name, std::u32string_view value)
        {
            this->pseudoElementName = std::u32string(name);
            this->pseudoElementValue = std::u32string(value);
        }
        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;

    private:
        std::u32string_view pseudoElementName;
        std::u32string_view pseudoElementValue;
    };

} // namespace WebVTT

#endif // PSEUDO_CLASS_SELECTOR_H