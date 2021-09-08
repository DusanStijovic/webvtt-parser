#include "elements/style_selectors/attribute_selectors/AttributeSelector.hpp"
#include "elements/style_selectors/attribute_selectors/LanguageSelector.hpp"
#include "elements/style_selectors/attribute_selectors/VoiceSelector.hpp"
#include "parser/CSSConstants.hpp"
#include "parser/ParserUtil.hpp"

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
  return nullptr;
}
bool AttributeSelector::isValueMatch(std::u32string_view valueToMatch) const {
  bool retValue = false;
  switch (this->stringMatchType) {

    case StringMatchType::UNDEFINED:retValue = false;
      break;
    case StringMatchType::NO_VALUE: retValue = true;
      break;
    case StringMatchType::EXACT_MATCHING:retValue = (valueToMatch == this->attributeValue);
      break;
    case StringMatchType::STARTS_WITH:retValue = this->attributeValue.starts_with(valueToMatch);
      break;
    case StringMatchType::ENDS_WITH: retValue = this->attributeValue.ends_with(valueToMatch);
      break;
    case StringMatchType::CONTAINS_SUBSTR:
      retValue = (this->attributeValue.find(valueToMatch) != std::u32string_view::npos);
      break;
    case StringMatchType::WHITE_SPACE_SEPERATED_WORDS: {
      std::u32string_view tempView = this->attributeValue;
      auto position = tempView.begin();
      std::u32string characters = {ParserUtil::SPACE_C, ParserUtil::TAB_C, ParserUtil::LF_C, ParserUtil::CR_C};
      retValue = false;
      while (position != tempView.end()) {
        auto temp = ParserUtil::parseUntilAnyOfGivenCharacters(tempView, characters, position);
        if (temp.empty()) break;
        if (temp == valueToMatch) {
          retValue = true;
          break;
        }
      }
      break;
    }
    case StringMatchType::EXACT_OR_FOLLOWED_BY_MINUS: {
      std::u32string_view tempView = this->attributeValue;
      auto position = tempView.begin();
      auto temp = ParserUtil::parseUntilCharacter(tempView, ParserUtil::HYPHEN_MINUS, position);
      retValue = (temp == valueToMatch);
      break;
    }
  }

  return retValue;
}
std::u32string_view AttributeSelector::getAttributeValue() const {
  return attributeValue;
}

} // namespace webvtt
