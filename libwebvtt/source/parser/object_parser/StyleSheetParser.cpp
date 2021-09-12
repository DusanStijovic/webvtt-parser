#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/cue_style_parser/states/StyleStartState.hpp"
#include "parser/cue_style_parser/ruleStates/StyleRulesState.hpp"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.hpp"
#include "logger/LoggingUtility.hpp"
#include "elements/style_selectors/CompoundSelector.hpp"
#include "elements/style_selectors/CombinatorSelector.hpp"

namespace webvtt {

void StyleSheetParser::addCSSRule(std::string_view name, std::string_view value) {
  for (auto &one : styleSheets) {

    one->addCSSRule(name, value);
  }
}

void StyleSheetParser::parseCSSRules(std::u32string_view newInput) {
  this->input = newInput;
  this->currentPosition = this->input.begin();
  setState(StyleState::StyleStateType::START);
  this->endParsing = false;
  this->buffer.clear();
  this->additionalBuffer.clear();
  this->compoundSelectorList.clear();
  this->combinatorSelectorList.clear();
  try {
    while (true) {
      currentState->processState(*this);
      if (endParsing)
        break;
      if (currentPosition != input.end()) currentPosition++;
    }
  }
  catch (const StyleSheetFormatError &error) {
    DILOGE(error.what());
  }
  catch (const NotImplementedError &error) {
    DILOGE(error.what());
  }
}

void
StyleSheetParser::addSelectorToCurrentCompoundSelectorList(std::unique_ptr<StyleSelector> styleSelector) {

  compoundSelectorList.push_back(std::move(styleSelector));
}

void StyleSheetParser::addSelectorToCurrentCombinatorSelectorList() {
  if (currentObject == nullptr)
    return;
  if (compoundSelectorList.size() == 1) {
    combinatorSelectorList.push_back(std::move(compoundSelectorList.back()));
    compoundSelectorList.pop_back();
  } else {
    std::unique_ptr<StyleSelector> help = std::make_unique<CompoundSelector>(compoundSelectorList);
    compoundSelectorList.clear();
    combinatorSelectorList.push_back(std::move(help));
  }
}

void
StyleSheetParser::setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator styleSelectorCombinator) {
  if (combinatorSelectorList.empty())
    return;
  combinatorSelectorList.back()->setStyleSelectorCombinator(styleSelectorCombinator);
}
void StyleSheetParser::setCurrentStyleSheetType(StyleSheet::StyleSheetType type) {
  this->currentSheetType = type;
}
void StyleSheetParser::addCurrentObjectToStyleSheetList() {
  styleSheets.push_back(std::move(currentObject));
}

void StyleSheetParser::addSelectorToCurrentObject() {

  if (combinatorSelectorList.size() == 1) {
    currentObject->setSelector(std::move(combinatorSelectorList.back()));
    combinatorSelectorList.clear();
  } else {
    auto help = std::make_unique<CombinatorSelector>(combinatorSelectorList);
    currentObject->setSelector(std::move(help));
  }
  combinatorSelectorList.clear();
}

}