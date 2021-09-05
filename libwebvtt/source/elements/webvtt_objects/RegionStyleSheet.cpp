#include "elements/webvtt_objects/RegionStyleSheet.hpp"

namespace webvtt {
StyleSheet::StyleSheetType RegionStyleSheet::getStyleSheetType() {
  return StyleSheet::StyleSheetType::REGION;
}
} // namespace webvtt
