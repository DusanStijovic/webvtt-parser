#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_ELEMENT_SELECTORS_PSEUDO_ELEMENT_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_ELEMENT_SELECTORS_PSEUDO_ELEMENT_SELECTOR_HPP_

#include "elements/style_selectors/StyleSelector.hpp"
#include <map>

namespace webvtt {
class PseudoElementSelector : public StyleSelector {
 public:


  [[nodiscard]] SelectorType getSelectorType() const override;

  static std::unique_ptr<StyleSelector> makeNewPseudoElementSelector(std::u32string_view type);

 private:
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_ELEMENT_SELECTOR_HPP_