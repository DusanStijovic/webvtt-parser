#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ID_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ID_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <string>

namespace webvtt {
class IDSelector : public StyleSelector {
 public:
  IDSelector(std::u32string_view new_id) : StyleSelector() {
    this->id = new_id;
  }
  SelectorType getSelectorType() const override;

 private:
  std::u32string id;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ID_SELECTOR_HPP_
