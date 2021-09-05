#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_VOICE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_VOICE_SELECTOR_HPP_
#include "AttributeSelector.hpp"

namespace webvtt {

class VoiceSelector : public AttributeSelector {
 public:
  explicit VoiceSelector(std::u32string_view value) : AttributeSelector(value) {}


};

}

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_ATTRIBUTE_SELECTORS_VOICE_SELECTOR_HPP_
