#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_COMPOUND_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_COMPOUND_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include "exceptions/NotImplementedError.hpp"
#include "logger/LoggingUtility.hpp"
#include <list>

namespace webvtt {
class CompoundSelector : public StyleSelector {
 public:
  explicit CompoundSelector(std::list<std::unique_ptr<StyleSelector>> &&newStyleSelectors) {
     this->styleSelectors = std::move(newStyleSelectors);
  }
  [[nosdiscard]] SelectorType getSelectorType() const override;

 private:
  std::list<std::unique_ptr<StyleSelector>> styleSelectors;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_COMPOUND_SELECTOR_HPP_
