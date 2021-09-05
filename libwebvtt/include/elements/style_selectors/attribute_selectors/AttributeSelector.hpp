#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"

namespace webvtt {

class AttributeSelector : public StyleSelector {
 public:
  explicit AttributeSelector(std::u32string_view value) {
    this->attributeValue = value;
    this->stringMatchType = StringMatchType::UNDEFINED;
  }



  enum class StringMatchType {
    UNDEFINED,
    NO_VALUE,
    EXACT_MATCHING,
    STARTS_WITH,
    ENDS_WITH,
    CONTAINS_SUBSTR,
    WHITE_SPACE_SEPERATED_WORDS,
    EXACT_OR_FOLLOWED_BY_MINUS

  };
  void setStringMatchingType(StringMatchType newStringMatchType);
  [[nodiscard]] StringMatchType getStringMatchingType() const;
  static std::unique_ptr <AttributeSelector> makeNewAttributeSelector(std::u32string_view type,
                                                                   std::u32string_view value);
  [[nodiscard]] SelectorType getSelectorType() const override;

 protected:
  std::u32string attributeValue;
  StringMatchType stringMatchType;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTOR_HPP_
