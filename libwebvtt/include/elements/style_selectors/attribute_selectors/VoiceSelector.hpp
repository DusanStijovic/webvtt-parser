#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_VOICE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_VOICE_SELECTOR_HPP_
#include "elements/style_selectors/attribute_selectors/AttributeSelector.hpp"

namespace webvtt {

class VoiceSelector : public AttributeSelector {
 public:
  explicit VoiceSelector(std::u32string_view value) : AttributeSelector(value) {}
  void accept(IStyleSelectorVisitor &visitor) const override;

};

}

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_VOICE_SELECTOR_HPP_
