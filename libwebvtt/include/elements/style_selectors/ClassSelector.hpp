#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_CLASS_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_CLASS_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <string>

namespace webvtt {

class ClassSelector : public StyleSelector {
 public:
  ClassSelector(std::u32string_view className) : StyleSelector() {
    this->className = className;
  }
  SelectorType getSelectorType() const override;

 private:
  std::u32string className;
};

} // namespace WebTT

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_CLASS_SELECTOR_HPP_
