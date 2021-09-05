#include "elements/style_selectors/IDSelector.hpp"

namespace webvtt
{
    StyleSelector::SelectorType
    IDSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::ID;
    }


} // namespace name
