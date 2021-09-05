#include "elements/style_selectors/StyleSelector.hpp"

namespace webvtt {

void StyleSelector::setStyleSelectorCombinator(StyleSelectorCombinator styleSelectorCombinator) {
  this->styleSelectorCombinator = styleSelectorCombinator;
}

StyleSelector::StyleSelectorCombinator StyleSelector::getStyleSelectorCombinator() const {
  return styleSelectorCombinator;
}

void StyleSelector::visit(const ItalicObject &object) {
  retValue = false;
}
void StyleSelector::visit(const ClassObject &object) {
  retValue = false;
}
void StyleSelector::visit(const BoldObject &object) {
  retValue = false;
}
void StyleSelector::visit(const RubyObject &object) {
  retValue = false;
}
void StyleSelector::visit(const RubyTextObject &object) {
  retValue = false;
}
void StyleSelector::visit(const UnderlineObject &object) {
  retValue = false;
}
void StyleSelector::visit(const VoiceObject &object) {
  retValue = false;
}
void StyleSelector::visit(const LanguageObject &object) {
  retValue = false;
}
void StyleSelector::visit(const RootObject &object) {
  retValue = false;
}
void StyleSelector::visit(const TimeStampObject &object) {
  retValue = false;
}
void StyleSelector::visit(const TextObject &object) {
  retValue = false;
}
void StyleSelector::connectCue(const Cue &cue) {
  connectedCue = &cue;
}
void StyleSelector::disconnectCue() {
  connectedCue = nullptr;
}

} // namespace webvtt
