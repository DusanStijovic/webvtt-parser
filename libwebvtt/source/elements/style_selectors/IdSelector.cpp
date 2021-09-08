#include "elements/style_selectors/IdSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
StyleSelector::SelectorType
IdSelector::getSelectorType() const {
  return StyleSelector::SelectorType::ID;
}

void IdSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
std::u32string_view IdSelector::getId() const {
  return id;
}
} // namespace voiceName
