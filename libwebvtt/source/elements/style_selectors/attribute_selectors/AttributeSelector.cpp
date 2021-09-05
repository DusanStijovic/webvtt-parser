#include "elements/style_selectors/attribute_selectors/AttributeSelector.hpp"
#include "elements/style_selectors/attribute_selectors/LanguageSelector.hpp"
#include "elements/style_selectors/attribute_selectors/VoiceSelector.hpp"
#include "parser/CSSConstants.hpp"

namespace webvtt {
void AttributeSelector::setStringMatchingType(StringMatchType newStringMatchType) {
  this->stringMatchType = newStringMatchType;
}

AttributeSelector::StringMatchType AttributeSelector::getStringMatchingType() const {
  return this->stringMatchType;
}

StyleSelector::SelectorType
AttributeSelector::getSelectorType() const {
  return StyleSelector::SelectorType::ATTRIBUTE;
}


std::unique_ptr<AttributeSelector> AttributeSelector::makeNewAttributeSelector(std::u32string_view type,
                                                                               std::u32string_view value) {
  if (type == CSSConstants::VOICE_ATTRIBUTE) {
    return std::make_unique<VoiceSelector>(value);
  }
  if (type == CSSConstants::LANGUAGE_ATTRIBUTE) {
    return std::make_unique<LanguageSelector>(value);
  }

}

} // namespace webvtt
