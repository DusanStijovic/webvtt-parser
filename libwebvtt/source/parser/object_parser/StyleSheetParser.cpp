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

void StyleSheetParser::buildObjectFromString(std::u32string_view newInput) {

  reset();
  this->input = newInput;
  this->currentPosition = this->input.begin();
  setState(StyleState::StyleStateType::START);

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
  reset();
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
void StyleSheetParser::saveStateBeforeComment() {
  savedStateBeforeComment = currentState;
}
void StyleSheetParser::goToStateBeforeComment() {
  currentState = savedStateBeforeComment;
  savedStateBeforeComment = nullptr;
}
void StyleSheetParser::reset() {
  combinatorSelectorList.clear();
  compoundSelectorList.clear();

  savedStateBeforeComment = nullptr;
  savedPseudoState = StyleState::StyleStateType::NONE;

  buffer.clear();
  additionalBuffer.clear();

  endParsing = false;
}

}