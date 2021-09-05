#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_CUE_STYLE_SHEET_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_CUE_STYLE_SHEET_HPP_

#include "elements/webvtt_objects/StyleSheet.hpp"

namespace webvtt {
class CueStyleSheet : public StyleSheet {
 public:

  StyleSheetType getStyleSheetType() override;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_CUE_STYLE_SHEET_HPP_