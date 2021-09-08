#include "elements/style_selectors/type_selectors/ClassTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt{
void ClassTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
}; // namespace webvtt