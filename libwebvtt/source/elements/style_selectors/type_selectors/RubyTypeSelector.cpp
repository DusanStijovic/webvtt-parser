#include "elements/style_selectors/type_selectors/RubyTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
void RubyTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
}; // namespace webvtt