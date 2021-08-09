#include "parser/StyleSheetParser.h"
#include "parser/cue_style_parser/states/StyleStartState.h"
#include "parser/cue_style_parser/cue_states/CueStyleStartSelectorState.h"
#include "parser/cue_style_parser/states/StyleRulesState.h"

namespace WebVTT
{

    void StyleSheetParser::initializeTokenizerStates()
    {
        statesInsance[StyleSheetParserState::START] = std::make_shared<StyleStartState>(*this);
     
        //TODO initialize all states
    }

    void StyleSheetParser::setState(StyleSheetParserState newState)
    {
        currentState = statesInsance[newState];
    }

    void StyleSheetParser::setSelectorToCurrentObject(std::shared_ptr<StyleSelector> styleSelector)
    {
        if (currentObject == nullptr)
            return;
        currentObject->setSelector(styleSelector);
    }
}