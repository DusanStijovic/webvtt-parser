#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_CLASS_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_CLASS_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <string>

namespace webvtt {

class ClassSelector : public StyleSelector {
 public:
  explicit ClassSelector(std::u32string_view className) {
    this->className = className;
  }
  [[nodiscard]] SelectorType getSelectorType() const override;

  void accept(IStyleSelectorVisitor &visitor) const override;

  [[nodiscard]]std::u32string_view getClassName() const;
 private:
  std::u32string className;
};

} // namespace WebTT

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_CLASS_SELECTOR_HPP_
