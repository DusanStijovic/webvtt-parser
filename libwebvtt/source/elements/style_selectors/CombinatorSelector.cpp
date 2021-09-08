#include "elements/style_selectors/CombinatorSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {

StyleSelector::SelectorType CombinatorSelector::getSelectorType() const {
  return StyleSelector::SelectorType::COMBINATOR;
}

void CombinatorSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
} // namespace webvtt