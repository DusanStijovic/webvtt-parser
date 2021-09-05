#include "elements/webvtt_objects/CueStyleSheet.hpp"

namespace webvtt {
StyleSheet::StyleSheetType CueStyleSheet::getStyleSheetType() {
  return StyleSheet::StyleSheetType::CUE;
}

} // namespace webvtt
