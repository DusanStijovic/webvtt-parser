#include "elements/style_selectors/attribute_selectors/VoiceSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt {
void VoiceSelector::accept(IStyleSelectorVisitor &visitor) const {
  visitor.visit(*this);
}
}