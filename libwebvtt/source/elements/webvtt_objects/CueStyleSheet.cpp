#include "elements/webvtt_objects/CueStyleSheet.hpp"

namespace webvtt {
StyleSheet::StyleSheetType CueStyleSheet::getStyleSheetType() {
  return StyleSheet::StyleSheetType::CUE;
}
bool CueStyleSheet::isSelectorAllowed(StyleSelector::SelectorType selectorType) const {
  //All type Allowed
  return true;
}

} // namespace webvtt
