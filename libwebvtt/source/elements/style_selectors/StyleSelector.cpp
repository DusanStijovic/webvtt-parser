#include "elements/style_selectors/StyleSelector.h"

namespace WebVTT
{

    StyleSelector::~StyleSelector() {}

    void StyleSelector::setStyleSelectorCombinator(StyleSelectorCombinator styleSelectorCombinator)
    {
        this->styleSelectorCombinator = styleSelectorCombinator;
    }

    StyleSelector::StyleSelectorCombinator StyleSelector::getStyleSelectorCombinator() const
    {
        return styleSelectorCombinator;
    };

} // namespace WebVTT
