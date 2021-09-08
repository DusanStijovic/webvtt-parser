#include "elements/style_selectors/StyleSelector.hpp"

namespace webvtt {

void StyleSelector::setStyleSelectorCombinator(StyleSelectorCombinator styleSelectorCombinator) {
  this->styleSelectorCombinator = styleSelectorCombinator;
}

StyleSelector::StyleSelectorCombinator StyleSelector::getStyleSelectorCombinator() const {
  return styleSelectorCombinator;
}


} // namespace webvtt
