#ifndef PSEUDO_CLASS_SELECTOR_H
#define PSEUDO_CLASS_SELECTOR_H
#include "elements/style_selectors/StyleSelector.h"
#include <map>

namespace WebVTT
{
    class PseudoClassSelector : public StyleSelector
    {
    public:
        PseudoClassSelector(std::u32string_view name, std::u32string_view value)
        {

            this->pseudoCLassName = std::u32string(name);
            this->pseudoClassValue = std::u32string(value);
        }
        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;

    private:
        std::u32string pseudoCLassName;
        std::u32string pseudoClassValue;
    };

} // namespace WebVTT

#endif // PSEUDO_CLASS_SELECTOR_H