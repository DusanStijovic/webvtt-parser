#include "elements/style_selectors/type_selectors/RubyTextTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {

void RubyTextTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
}; // namespace webvtt