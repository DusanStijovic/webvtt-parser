#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/cue_style_parser/states/StyleStartState.hpp"
#include "parser/cue_style_parser/ruleStates/StyleRulesState.hpp"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.hpp"
#include "logger/LoggingUtility.hpp"
#include "elements/style_selectors/CompoundSelector.hpp"

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
  try {
    while (true) {
      currentState->processState(*this);
      if (endParsing)
        break;
      currentPosition++;
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
StyleSheetParser::addSelectorToCurrentSelectorList(std::unique_ptr<StyleSelector> styleSelector) {

  compoundSelectorList.push_back(std::move(styleSelector));
}

void StyleSheetParser::addSelectorToCurrentObject() {
  if (currentObject == nullptr)
    return;
  if (compoundSelectorList.size() == 1) {
    currentObject->addSelector(std::move(compoundSelectorList.back()));
    compoundSelectorList.pop_back();
  } else {
    std::unique_ptr<StyleSelector> help = std::make_unique<CompoundSelector>(std::move(compoundSelectorList));
    compoundSelectorList.clear();
    currentObject->addSelector(std::move(help));
  }
}

void
StyleSheetParser::setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator styleSelectorCombinator) {
  if (currentObject->getSelectors().empty())
    return;
  currentObject->getSelectors().back()->setStyleSelectorCombinator(styleSelectorCombinator);
}
void StyleSheetParser::setCurrentStyleSheetType(StyleSheet::StyleSheetType type) {
  this->currentSheetType = type;
}
void StyleSheetParser::addCurrentObjectToStyleSheetList() {
  styleSheets.push_back(std::move(currentObject));
}

}