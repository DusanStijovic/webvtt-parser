#include "elements/style_selectors/type_selectors/UnderlineTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"


namespace webvtt {
void UnderlineTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
} // namespace webvtt