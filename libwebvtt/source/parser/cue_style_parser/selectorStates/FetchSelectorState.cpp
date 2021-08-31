#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    void FetchSelectorState::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter(parser);
        bool processDone = additionalBehaviour(parser, character);

        StyleSelector::StyleSelectorCombinator combinator = StyleSelector::StyleSelectorCombinator::NONE;

        if (processDone)
            return;

        switch (character)
        {
        case ParserUtil::LF_C:
        case ParserUtil::TAB_C:
        case ParserUtil::SPACE_C:
            combinator = StyleSelector::StyleSelectorCombinator::DESCENDANT;
            foundCombinatorCharacter(parser, combinator);
            break;
        case ParserUtil::PLUS_SIGN_C:
            combinator = StyleSelector::StyleSelectorCombinator::NEXT_SIBLING;
            foundCombinatorCharacter(parser, combinator);
            break;
        case ParserUtil::HYPHEN_GREATER:
            combinator = StyleSelector::StyleSelectorCombinator::CHILD;
            foundCombinatorCharacter(parser, combinator);
            break;
        case ParserUtil::TILDE_C:
            combinator = StyleSelector::StyleSelectorCombinator::SUBSEQUENT_SIBLING;
            foundCombinatorCharacter(parser, combinator);
            break;

        case ParserUtil::HASHTAG_C:
        case ParserUtil::COLON_C:
        case ParserUtil::DOT_C:
            foundCompoundCharacter(parser);
            break;

        case ParserUtil::COMMA_C:
            foundCommaCharacter(parser);
            break;

        case ParserUtil::RIGHT_PARENTHESIS_C:
            foundRightParenthes(parser);
            break;

        case StyleSheetParser::STOP_PARSER:
            foundStopTokenizer(parser);
            break;

        default:
            foundDefaultBehaviour(parser, character);
            break;
        }
    }

    void FetchSelectorState::foundCommaCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector)
    {

        parser.addSelectorToCurrentSelectorList(std::move(styleSelector));
        parser.addSelectorToCurrentObject();
        parser.goToSavedState();
    }

    void FetchSelectorState::foundCombinatorCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector)
    {
        parser.addSelectorToCurrentSelectorList(std::move(styleSelector));
        parser.addSelectorToCurrentObject();
    }

    void FetchSelectorState::foundCompoundCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector)
    {
        parser.addSelectorToCurrentSelectorList(std::move(styleSelector));
        parser.goToSavedState();
        parser.getCurrentPosition()--;
    }

    void FetchSelectorState::foundRightParenthes(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector)
    {
        parser.addSelectorToCurrentSelectorList(std::move(styleSelector));
        parser.addSelectorToCurrentObject();
        parser.setState(StyleState::StyleStateType::END_SELECTOR);
        parser.getCurrentPosition()--;
    }

    void FetchSelectorState::foundStopTokenizer(StyleSheetParser &parser)
    {
        parser.setState(StyleState::StyleStateType::ERROR);
    }

    void FetchSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character)
    {
        parser.getBuffer().push_back(character);
    };

    bool FetchSelectorState::additionalBehaviour(StyleSheetParser &parser, uint32_t character)
    {
        return false;
    }

    void FetchSelectorState::preprocessBuffer(StyleSheetParser &parser)
    {
    }

    std::unique_ptr<StyleSelector> FetchSelectorState::makeNewStyleSelector(StyleSheetParser &parser)
    {
        return nullptr;
    }

    void FetchSelectorState::foundCombinatorCharacter(StyleSheetParser &parser, StyleSelector::StyleSelectorCombinator styleCombinator)
    {
        preprocessBuffer(parser);
        foundCombinatorCharacter(parser, makeNewStyleSelector(parser));
        parser.setCombinatorToMostRecentSelector(styleCombinator);
    };

    void FetchSelectorState::foundCompoundCharacter(StyleSheetParser &parser)
    {
        preprocessBuffer(parser);
        foundCompoundCharacter(parser, makeNewStyleSelector(parser));
    };

    void FetchSelectorState::foundRightParenthes(StyleSheetParser &parser)
    {
        preprocessBuffer(parser);
        foundRightParenthes(parser, makeNewStyleSelector(parser));
        parser.setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator::NONE);
    };

    void FetchSelectorState::foundCommaCharacter(StyleSheetParser &parser)
    {
        preprocessBuffer(parser);
        foundCommaCharacter(parser, makeNewStyleSelector(parser));
        parser.setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator::MULTIPLE);
    }

} // namespace WebVTT
