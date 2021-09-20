#include "elements/webvtt_objects/RegionStyleSheet.hpp"

namespace webvtt {
StyleSheet::StyleSheetType RegionStyleSheet::getStyleSheetType() {
  return StyleSheet::StyleSheetType::REGION;
}
bool RegionStyleSheet::isSelectorAllowed(StyleSelector::SelectorType selectorType) const {
  if (selectorType == StyleSelector::SelectorType::ID) return true;
  return false;
}
} // namespace webvtt
