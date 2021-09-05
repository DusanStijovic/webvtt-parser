#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_MATCH_ALL_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_MATCH_ALL_SELECTOR_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include "elements/rules_filters/RuleFilter.hpp"

namespace webvtt {
class MatchAllSelector : public StyleSelector {
 public:
  MatchAllSelector() : StyleSelector() {}

  SelectorType getSelectorType() const override;
};
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_MATCH_ALL_SELECTOR_HPP_
