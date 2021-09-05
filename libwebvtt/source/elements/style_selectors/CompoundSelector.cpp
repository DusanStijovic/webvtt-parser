#include "elements/style_selectors/CompoundSelector.hpp"

namespace webvtt
{
    StyleSelector::SelectorType
    CompoundSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::COMPOUND;
    }



} // namespace webvtt
