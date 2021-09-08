#ifndef LIBWEBVTT_SOURCE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_LANGUAGE_SELECTOR_HPP_
#define LIBWEBVTT_SOURCE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_LANGUAGE_SELECTOR_HPP_
#include "elements/style_selectors/attribute_selectors/AttributeSelector.hpp"

namespace webvtt {

class LanguageSelector : public AttributeSelector {

 public:
  explicit LanguageSelector(std::u32string_view value) : AttributeSelector(value) {};
  void accept(IStyleSelectorVisitor &visitor) const override;

};

} // namespace webvtt

#endif // LIBWEBVTT_SOURCE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_LANGUAGE_SELECTOR_HPP_
