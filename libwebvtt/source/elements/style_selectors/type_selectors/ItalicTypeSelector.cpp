#include "elements/style_selectors/type_selectors/ItalicTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
void ItalicTypeSelector::accept(IStyleSelectorVisitor &visitor)  const {
  visitor.visit(*this);
}
}; // namespace web