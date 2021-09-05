#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_CLASS_SELECTORS_PSEUDO_CLASS_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_CLASS_SELECTORS_PSEUDO_CLASS_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <map>

namespace webvtt {
class PseudoClassSelector : public StyleSelector {
 public:

  [[nodiscard]] SelectorType getSelectorType() const override;
  static std::unique_ptr<StyleSelector> makeNewPseudoClassSelector(std::u32string_view type);
 private:
};

} // namespace webvtt

#endif //LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_CLASS_SELECTORS_PSEUDO_CLASS_SELECTOR_HPP_