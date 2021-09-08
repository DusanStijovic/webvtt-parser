#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_STYLE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_STYLE_SELECTOR_HPP_
#include "elements/rules_filters/RuleFilter.hpp"
#include <set>
#include <string>
#include <map>

namespace webvtt {
class IStyleSelectorVisitor;

class StyleSelector {

 public:
  StyleSelector() {
    this->styleSelectorCombinator = StyleSelectorCombinator::NONE;
    this->retValue = false;
  };
  enum class SelectorType {
    ID,
    ATTRIBUTE,
    CLASS,
    TYPE,
    PSEUDO_CLASS,
    PSEUDO_ELEMENT,
    MATCH_ALL,
    COMPOUND,
    COMBINATOR
  };

  enum class StyleSelectorCombinator {
    UNDEFINED,
    NONE,
    MULTIPLE,
    DESCENDANT,
    CHILD,
    NEXT_SIBLING,
    SUBSEQUENT_SIBLING
  };

  void setStyleSelectorCombinator(StyleSelectorCombinator styleSelectorCombinator);
  [[nodiscard]] StyleSelectorCombinator getStyleSelectorCombinator() const;
  [[nodiscard]] virtual SelectorType getSelectorType() const = 0;

  virtual void accept(IStyleSelectorVisitor &) const = 0;

  StyleSelector(const StyleSelector &) = delete;
  StyleSelector(StyleSelector &&) = delete;
  StyleSelector &operator=(const StyleSelector &) = delete;
  StyleSelector &operator=(StyleSelector &&) = delete;
  virtual ~StyleSelector() = default;

 protected:
  StyleSelectorCombinator styleSelectorCombinator;
  bool retValue = false;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_STYLE_SELECTOR_HPP_
