
#include "parser/cue_style_parser/states/StyleState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/cue_style_parser/states/StyleStartState.hpp"
#include "parser/cue_style_parser/selectorStates/StyleAttributeSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StyleClassSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StyleEndSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StyleIdSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StylePseudoClassSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StylePseudoElementSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StylePseudoClassWithArgumentEndState.hpp"
#include "parser/cue_style_parser/selectorStates/StylePseudoElementWithArgumentEndState.hpp"
#include "parser/cue_style_parser/selectorStates/StyleStartPseudoState.hpp"
#include "parser/cue_style_parser/ruleStates/StyleRulesState.hpp"
#include "parser/cue_style_parser/cue_states/StyleStartSelectorState.hpp"
#include "parser/cue_style_parser/selectorStates/StyleTypeSelectorState.hpp"
#include "parser/cue_style_parser/ruleStates/BeforeRuleStartState.hpp"
#include "parser/cue_style_parser/states/EndStyleState.hpp"
#include "parser/cue_style_parser/states/ErrorStyleState.hpp"

namespace webvtt
{

    std::map<StyleState::StyleStateType, std::unique_ptr<StyleState>> StyleState::statesInstance;

    uint32_t StyleState::getNextCharacter(StyleSheetParser &parser)
    {
        uint32_t character;
        if (parser.getCurrentPosition() == parser.getInput().end())
            character = StyleSheetParser::STOP_PARSER;
        else
        {
            character = *parser.getCurrentPosition();
        }
        return character;
    }

    std::unique_ptr<StyleState>
    StyleState::makeNewState(StyleStateType styleStateType)
    {
        switch (styleStateType)
        {
        case StyleStateType::ATTRIBUTE_SELECTOR:
            return std::make_unique<StyleAttributeSelectorState>();
            break;
        case StyleStateType::CLASS_SELECTOR:
            return std::make_unique<StyleClassSelectorState>();
            break;
            case StyleStateType::START_SELECTOR:
            return std::make_unique<StyleStartSelectorState>();
            break;
        case StyleStateType::END_SELECTOR:
            return std::make_unique<StyleEndSelectorState>();
            break;
        case StyleStateType::PSEUDO_CLASS_SELECTOR:
            return std::make_unique<StylePseudoClassSelectorState>();
            break;
        case StyleStateType::PSEUDO_ELEMENT_SELECTOR:
            return std::make_unique<StylePseudoElementSelectorState>();
            break;
        case StyleStateType::PSEUDO_START:
            return std::make_unique<StyleStartPseudoState>();
            break;
        case StyleStateType::PSEDO_CLASS_ARGUMENT_END:
            return std::make_unique<StylePseudoClassWithArgumentEndState>();
            break;
        case StyleStateType::PSEDO_ELEMENT_ARGUMENT_END:
            return std::make_unique<StylePseudoElementWithArgumentEndState>();
            break;
        case StyleStateType::BEFORE_RULE_STATE:
            return std::make_unique<BeforeRuleStartState>();
        case StyleStateType::RULES:
            return std::make_unique<StyleRulesState>();
            break;
        case StyleStateType::START:
            return std::make_unique<StyleStartState>();
            break;
        case StyleStateType::TYPE_SELECTOR:
            return std::make_unique<StyleTypeSelectorState>();
            break;
        case StyleStateType::ID_SELECTOR:
            return std::make_unique<StyleIdSelectorState>();
            break;
        case StyleStateType::END_STATE:
            return std::make_unique<EndStyleState>();
            break;
        case StyleStateType::ERROR:
          return std::make_unique<ErrorStyleState>();
            break;
        default:
            return nullptr;
            break;
        }
    }

    StyleState *StyleState::getInstance(StyleStateType newState)
    {
        auto found = statesInstance.find(newState);
        if (found == statesInstance.end())
        {
            return (statesInstance[newState] = StyleState::makeNewState(newState)).get();
        }
        else
        {
            return found->second.get();
        }
    }

} // namespace webvtt
