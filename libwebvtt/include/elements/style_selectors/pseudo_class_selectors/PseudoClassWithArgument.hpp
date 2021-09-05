#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_CLASS_SELECTORS_PSEUDO_CLASS_WITH_ARGUMENT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_CLASS_SELECTORS_PSEUDO_CLASS_WITH_ARGUMENT_HPP_
#include "elements/style_selectors/StyleSelector.hpp"
#include <memory>

namespace webvtt {

class PseudoClassWithArgument : StyleSelector {
 public:

  explicit PseudoClassWithArgument(std::u32string_view newValue) : value(newValue) {}

  static std::unique_ptr<StyleSelector> makeNewPseudoClassWithArgument(std::u32string_view type,
                                                                       std::u32string_view value);
 protected:
  std::u32string value;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_PSEUDO_CLASS_SELECTORS_PSEUDO_CLASS_WITH_ARGUMENT_HPP_
