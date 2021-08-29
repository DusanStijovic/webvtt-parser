#include "parser/StyleSheetParser.h"
#include "parser/cue_style_parser/states/StyleStartState.h"
#include "parser/cue_style_parser/ruleStates/StyleRulesState.h"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.h"
#include "logger/LoggingUtility.h"
#include "elements/style_objects/CompoundSelector.h"

namespace WebVTT
{

    void StyleSheetParser::setState(StyleState::StyleStateType newState)
    {
        auto found = statesInstance.find(newState);
        if (found == statesInstance.end())
        {
            currentState = (statesInstance[newState] = StyleState::makeNewState(*this, newState)).get();
        }
        else
        {
            currentState = found->second.get();
        }
    }

    void StyleSheetParser::addCSSRule(std::string name, std::string value)
    {

        currentObject->addCSSRule(name, value);
    }

    void StyleSheetParser::parseCSSRules(std::u32string_view newInput)
    {
        this->input = newInput;
        this->currentPosition = this->input.begin();
        setState(StyleState::StyleStateType::START);
        this->endParsing = false;
        this->buffer.clear();
        this->additionalBuffer.clear();
        this->compoundSelectorList.clear();
        try
        {
            while (true)
            {
                currentState->processState();
                // if (endParsing)
                //     break;
                currentPosition++;
            }
        }
        catch (const StyleSheetFormatError &error)
        {
            DILOGE(error.what());
        }
    }

    void
    StyleSheetParser::addSelectorToCurrentSelectorList(std::unique_ptr<StyleSelector> &&styleSelector)
    {

        compoundSelectorList.push_back(std::move(styleSelector));
    }

    void StyleSheetParser::addSelectorToCurrentObject()
    {
        if (currentObject == nullptr)
            return;
        if (compoundSelectorList.size() == 1)
        {
            currentObject->addSelector(std::move(compoundSelectorList.back()));
            compoundSelectorList.pop_back();
        }
        else
        {
            std::unique_ptr<StyleSelector> help = std::make_unique<CompoundSelector>(std::move(compoundSelectorList));
            compoundSelectorList.clear();
            currentObject->addSelector(std::move(help));
        }
    }

    void StyleSheetParser::addCurrentObjectToStyleSheetList()
    {
        styleSheets.push_back(std::move(currentObject));
        currentObject = nullptr;
    }

    void
    StyleSheetParser::setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator styleSelectorCombinator)
    {
        if (currentObject->getSelectors().empty())
            return;
        currentObject->getSelectors().back()->setStyleSelectorCombinator(styleSelectorCombinator);
    }
}