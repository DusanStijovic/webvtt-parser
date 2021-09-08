#include "elements/style_selectors/type_selectors/VoiceTypeSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
void VoiceTypeSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}


} // namespace webvtt