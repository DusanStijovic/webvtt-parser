#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_STYLE_SHEET_PARSER_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_STYLE_SHEET_PARSER_HPP_

#include "parser/object_parser/base_classes/StyleSheetParserBase.hpp"
#include "parser/cue_style_parser/states/StyleState.hpp"
#include "state_machine/StateMachineForParsingText.hpp"
#include "buffer/UniquePtrSyncBuffer.hpp"
#include "elements/webvtt_objects/StyleSheet.hpp"

#include <map>
#include <memory>
#include <string>
#include <list>

namespace webvtt {


class StyleSheetParser : public StyleSheetParserBase,
                         public StateMachineForParsingText<StyleState, StyleState::StyleStateType> {
 public:
  constexpr static std::u32string_view CUE_STYLE_START = U"::cue";
  constexpr static std::u32string_view REGION_STYLE_START = U"::cue-region";
  constexpr static uint32_t STOP_PARSER = 0xFFFF;

  StyleSheetParser() {
    currentState = StyleState::getInstance(StyleState::StyleStateType::START);
  }


  void buildObjectFromString(std::u32string_view input) override;
  void addCSSRule(std::string_view name, std::string_view value);

  void addSelectorToCurrentCombinatorSelectorList();
  void addSelectorToCurrentCompoundSelectorList(std::unique_ptr<StyleSelector> styleSelector);
  void addSelectorToCurrentObject();

  void setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator styleSelectorCombinator);

  void addCurrentObjectToStyleSheetList();

  inline std::u32string &getBuffer() { return buffer; }
  inline std::u32string &getAdditionalBuffer() { return additionalBuffer; }

  inline void setEndParsing(bool isEnd) { this->endParsing = isEnd; }
  [[nodiscard]] inline bool isEndParsing() const { return endParsing; }

  void setCurrentStyleSheetType(StyleSheet::StyleSheetType type);

  void goToSavedPseudoState() { setState(savedPseudoState); }
  void savePseudoState(StyleState::StyleStateType styleStateType) { savedPseudoState = styleStateType; }

  StyleSheetParser(const StyleSheetParser &) = delete;
  StyleSheetParser(StyleSheetParser &&) = delete;
  StyleSheetParser &operator=(const StyleSheetParser &) = delete;
  StyleSheetParser &operator=(StyleSheetParser &&) = delete;
  ~StyleSheetParser() override = default;

 private:
  bool endParsing = false;

  StyleSheet::StyleSheetType currentSheetType = StyleSheet::StyleSheetType::UNDEFINED;

  std::u32string buffer;
  std::u32string additionalBuffer;

  StyleState::StyleStateType savedState = StyleState::StyleStateType::NONE;
  StyleState::StyleStateType savedPseudoState = StyleState::StyleStateType::NONE;

  std::list<std::unique_ptr<StyleSelector>> combinatorSelectorList;
  std::list<std::unique_ptr<StyleSelector>> compoundSelectorList;

};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_STYLE_SHEET_PARSER_HPP_