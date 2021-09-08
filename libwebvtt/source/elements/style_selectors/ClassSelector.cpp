#include "elements/style_selectors/ClassSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
StyleSelector::SelectorType
ClassSelector::getSelectorType() const {
  return StyleSelector::SelectorType::CLASS;
}
void ClassSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
std::u32string_view ClassSelector::getClassName() const {
  return className;
}

} // namespace webvtt
