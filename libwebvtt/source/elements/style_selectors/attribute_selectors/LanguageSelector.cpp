#include "elements/style_selectors/attribute_selectors/LanguageSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt{
void LanguageSelector::accept(IStyleSelectorVisitor &visitor)  const {
  visitor.visit(*this);
}
}