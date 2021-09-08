#include "elements/style_selectors/MatchAllSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
StyleSelector::SelectorType
MatchAllSelector::getSelectorType() const {
  return StyleSelector::SelectorType::MATCH_ALL;
}
void MatchAllSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}

} // namespace webvtt
