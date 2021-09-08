#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_COMBINATOR_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_COMBINATOR_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include "exceptions/NotImplementedError.hpp"
#include "logger/LoggingUtility.hpp"
#include <list>

namespace webvtt {
class CombinatorSelector : public StyleSelector {
 public:
  explicit CombinatorSelector(std::list<std::unique_ptr<StyleSelector>> &newStyleSelectors) {
    std::move(newStyleSelectors.begin(), newStyleSelectors.end(), std::back_inserter(this->styleSelectors));
    newStyleSelectors.clear();
  }
  [[nodiscard]] SelectorType getSelectorType() const override;
  void accept(IStyleSelectorVisitor &visitor) const override;

 private:
  std::list<std::unique_ptr<StyleSelector>> styleSelectors;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_COMPOUND_SELECTOR_HPP_
