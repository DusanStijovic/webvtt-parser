#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_TYPE_SELECTORS_TYPE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_TYPE_SELECTORS_TYPE_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <string>
#include <memory>

namespace webvtt {
class TypeSelector : public StyleSelector {
 public:
  [[nodiscard]] SelectorType getSelectorType() const override;
  static std::unique_ptr<StyleSelector> makeNewTypeSelector(std::u32string_view type);

};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_TYPE_SELECTORS_TYPE_SELECTOR_HPP_
