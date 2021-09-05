#include "elements/style_selectors/MatchAllSelector.hpp"

namespace webvtt
{
    StyleSelector::SelectorType
    MatchAllSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::MATCH_ALL;
    }


} // namespace webvtt
