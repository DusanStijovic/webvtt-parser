#include "elements/style_selectors/type_selectors/LanguageTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
void LanguageTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
} // namespace webvtt