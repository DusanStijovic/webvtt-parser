#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ID_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ID_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <string>

namespace webvtt {
class IdSelector : public StyleSelector {
 public:
  explicit IdSelector(std::u32string_view new_id) {
    this->id = new_id;
  }
  [[nodiscard]]std::u32string_view getId() const;
  [[nodiscard]]SelectorType getSelectorType() const override;
  void accept(IStyleSelectorVisitor &visitor) const override;

 private:
  std::u32string id;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ID_SELECTOR_HPP_
