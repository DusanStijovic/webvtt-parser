#include "elements/style_selectors/ClassSelector.hpp"

namespace webvtt
{
    StyleSelector::SelectorType
    ClassSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::CLASS;
    }



} // namespace webvtt
