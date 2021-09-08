#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_TYPE_SELECTORS_RUBY_TEXT_TYPE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_TYPE_SELECTORS_RUBY_TEXT_TYPE_SELECTOR_HPP_
#include "elements/style_selectors/type_selectors/TypeSelector.hpp"

namespace webvtt {
class RubyTextTypeSelector : public TypeSelector {
  void accept(IStyleSelectorVisitor &visitor) const override;

};
} // namespace webvtt



#endif //LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_TYPE_SELECTORS_RUBY_TEXT_TYPE_SELECTOR_HPP_
