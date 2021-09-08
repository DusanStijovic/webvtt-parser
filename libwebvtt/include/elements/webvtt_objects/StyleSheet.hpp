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
class ICueTreeVisitor;

class StyleSheet : public Block {
 public:
  enum class StyleSheetType {
    UNDEFINED,
    CUE,
    REGION
  };

  void setSelector(std::unique_ptr<StyleSelector> newSelector);
  [[nodiscard]] const StyleSelector &getSelector() const;

  void addCSSRule(std::string_view name, std::string_view newValue);
  [[maybe_unused]] const std::map<std::string, std::string> &getCSSRules();

  virtual StyleSheetType getStyleSheetType() = 0;
  static std::unique_ptr<StyleSheet> makeNewStyleSheet(StyleSheetType styleSheetType);




 protected:
  std::map<std::string, std::string> cssRules;
  std::unique_ptr<StyleSelector> styleSelector;

};

}

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_STYLE_SHEET_HPP_
