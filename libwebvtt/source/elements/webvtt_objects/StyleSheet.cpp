#include "elements/webvtt_objects/StyleSheet.hpp"
#include "elements/webvtt_objects/CueStyleSheet.hpp"
#include "elements/webvtt_objects/RegionStyleSheet.hpp"

namespace webvtt {
void StyleSheet::setSelector(std::unique_ptr<StyleSelector> newSelector) {
  this->styleSelector = std::move(newSelector);
}

void StyleSheet::addCSSRule(std::string_view name, std::string_view newValue) {
  auto temp = std::string(name);
  cssRules[temp] = newValue;
}

std::unique_ptr<StyleSheet> StyleSheet::makeNewStyleSheet(StyleSheetType styleSheetType) {
  switch (styleSheetType) {
    case StyleSheetType::CUE:return std::make_unique<CueStyleSheet>();
      break;
    case StyleSheetType::REGION:return std::make_unique<RegionStyleSheet>();
      break;
    default:return nullptr;
      break;
  }
}

const std::map<std::string, std::string> &StyleSheet::getCSSRules() {
  return cssRules;
}

const StyleSelector &StyleSheet::getSelector() const {
  return *styleSelector;
}

} // namespace webvtt
