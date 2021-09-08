#include "elements/style_selectors/type_selectors/BoldTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
void BoldTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
}; // namespace webvtt