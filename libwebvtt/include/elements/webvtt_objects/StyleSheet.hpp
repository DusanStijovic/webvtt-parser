#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_STYLE_SHEET_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_STYLE_SHEET_HPP_

#include "elements/webvtt_objects/Block.hpp"
#include "elements/style_selectors/StyleSelector.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"
#include <memory>
#include <map>
#include <string>
#include <list>

namespace webvtt {
class Cue;
class NodeObject;
class Region;

class StyleSheet : public Block {
 public:
  enum class StyleSheetType {
    UNDEFINED,
    CUE,
    REGION
  };

  void addSelector(std::unique_ptr<StyleSelector> &&newSelector);
  std::list<std::unique_ptr<StyleSelector>> &getSelectors();

  void addCSSRule(std::string_view name, std::string_view newValue);
  const std::map<std::string, std::string> &getCSSRules();

  virtual StyleSheetType getStyleSheetType() = 0;
  static std::unique_ptr<StyleSheet> makeNewStyleSheet(StyleSheetType styleSheetType);

  void setCurrentCue(const Cue &cue);

 protected:
  std::map<std::string, std::string> cssRules;
  std::list<std::unique_ptr<StyleSelector>> styleSelectors;
  bool retShouldApply = false;
  const Cue *connectedCue = nullptr;

};

}

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_STYLE_SHEET_HPP_
