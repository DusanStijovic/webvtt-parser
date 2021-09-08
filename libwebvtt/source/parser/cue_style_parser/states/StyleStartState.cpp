#include "parser/cue_style_parser/states/StyleStartState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/webvtt_objects/RegionStyleSheet.hpp"
#include "elements/webvtt_objects/CueStyleSheet.hpp"
#include "elements/style_selectors/MatchAllSelector.hpp"

namespace webvtt
{

    StyleSheet::StyleSheetType StyleStartState::decideStyleSheetType(std::u32string_view input)
    {
        bool isCue = (StyleSheetParser::CUE_STYLE_START == input);
        bool isCueRegion = (StyleSheetParser::REGION_STYLE_START == input);

        if (isCue)
            return StyleSheet::StyleSheetType::CUE;
        if (isCueRegion)
            return StyleSheet::StyleSheetType::REGION;

        return StyleSheet::StyleSheetType::UNDEFINED;
    }

    void StyleStartState::decideNextStateWithSelector(StyleSheetParser &parser, StyleSheet::StyleSheetType styleSheetType)
    {
        switch (styleSheetType)
        {
        case StyleSheet::StyleSheetType::CUE:
            parser.saveState(StyleState::StyleStateType::CUE_START_SELECTOR);
            parser.setState(StyleState::StyleStateType::CUE_START_SELECTOR);
            break;
        case StyleSheet::StyleSheetType::REGION:
            parser.saveState(StyleState::StyleStateType::CUE_REGION_START_SELECTOR);
            parser.setState(StyleState::StyleStateType::CUE_REGION_START_SELECTOR);
            break;
        default:
            parser.setState(StyleState::StyleStateType::ERROR);
            break;
        }
    }

    StyleSheet::StyleSheetType StyleStartState::makeAndSetNewStyleSheetForParsing(StyleSheetParser &parser)
    {
        ParserUtil::strip(parser.getBuffer(), ParserUtil::isASCIIWhiteSpaceCharacter);
        auto type = decideStyleSheetType(parser.getBuffer());
        parser.setNewObjectForParsing(StyleSheet::makeNewStyleSheet(type));
        parser.getBuffer().clear();
        return type;
    }

    void StyleStartState::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter(parser);

        switch (character)
        {
        case ParserUtil::LEFT_PARENTHESIS_C:
        {
            auto madeType = makeAndSetNewStyleSheetForParsing(parser);
            decideNextStateWithSelector(parser, madeType);

            break;
        }
        case ParserUtil::LEFT_CURLY_BRACKET_C:
        case ParserUtil::COMMA_C:
        {
            makeAndSetNewStyleSheetForParsing(parser);
          parser.addSelectorToCurrentCompoundSelectorList(std::make_unique<MatchAllSelector>());
          parser.addSelectorToCurrentCombinatorSelectorList();
            parser.getCurrentPosition()--;
            parser.setState(StyleState::StyleStateType::BEFORE_RULE_STATE);
            break;
        }
        case StyleSheetParser::STOP_PARSER:
            parser.setState(StyleState::StyleStateType::ERROR);
            break;

        default:
            parser.getBuffer().push_back(character);
            break;
        }
    }
}