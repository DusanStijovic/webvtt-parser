#ifndef STYLE_SHEET_PARSER_H
#define STYLE_SHEET_PARSER_H

#include "parser/ObjectParser.h"
#include "parser/cue_style_parser/states/StyleState.h"
#include "state_machine/StateMachineForParsingText.h"
#include "buffer/UniquePtrSyncBuffer.h"
#include "elements/webvtt_objects/StyleSheet.h"

#include <map>
#include <memory>
#include <string>
#include <list>

namespace WebVTT
{
  class StyleSheetParser : public ObjectParser<StyleSheet>,
                           public StateMachineForParsingText<StyleState, StyleState::StyleStateType>
  {
  public:
    constexpr static std::u32string_view CUE_STYLE_START = U"::cue";
    constexpr static std::u32string_view REGION_STYLE_START = U"::cue-region";
    constexpr static uint32_t STOP_PARSER = 0xFFFF;

    StyleSheetParser()
    {
      currentState = StyleState::getInstance(StyleState::StyleStateType::START);
    }

    inline std::list<std::unique_ptr<StyleSheet>> &getParsedStyleSheets() { return styleSheets; }

    void parseCSSRules(std::u32string_view input);
    void addCSSRule(std::string name, std::string value);

    void addSelectorToCurrentObject();
    void addSelectorToCurrentSelectorList(std::unique_ptr<StyleSelector> &&styleSelector);
    void addCurrentObjectToStyleSheetList();
    void setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator styleSelectorCombinator);

    inline std::u32string &getBuffer() { return buffer; }
    inline std::u32string &getAdditionalBuffer() { return additionalBuffer; }

    inline void setEndParsing(bool isEnd) { this->endParsing = isEnd; }
    [[nodiscard]] inline bool isEndParsing() const { return endParsing; }

    void goToSavedState() { setState(savedState); }
    void saveState(StyleState::StyleStateType styleStateType) { savedState = styleStateType; }

    void goToSavedPseudoState() { setState(savedPseudoState); }
    void savePseudoState(StyleState::StyleStateType styleStateType) { savedPseudoState = styleStateType; }

  private:
    bool endParsing = false;

    std::u32string buffer;
    std::u32string additionalBuffer;

    StyleState::StyleStateType savedState = StyleState::StyleStateType::NONE;
    StyleState::StyleStateType savedPseudoState = StyleState::StyleStateType::NONE;

    std::list<std::unique_ptr<StyleSheet>> styleSheets;
    std::list<std::unique_ptr<StyleSelector>> compoundSelectorList;
  };
}

#endif