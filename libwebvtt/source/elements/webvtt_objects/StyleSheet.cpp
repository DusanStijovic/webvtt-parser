#include "elements/webvtt_objects/StyleSheet.hpp"
#include "elements/webvtt_objects/CueStyleSheet.hpp"
#include "elements/webvtt_objects/RegionStyleSheet.hpp"

namespace webvtt {
void StyleSheet::addSelector(std::unique_ptr<StyleSelector> &&newSelector) {
  this->styleSelectors.push_back(std::move(newSelector));
}

void StyleSheet::addCSSRule(std::string_view name, std::string_view newValue) {

  cssRules[std::string(name)] = newValue;
}

std::list<std::unique_ptr<StyleSelector>> &StyleSheet::getSelectors() {
  return styleSelectors;
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


void StyleSheet::setCurrentCue(const Cue &cue) {
  connectedCue = &cue;
};

const std::map<std::string, std::string> &StyleSheet::getCSSRules() {
  return cssRules;
}

} // namespace webvtt
