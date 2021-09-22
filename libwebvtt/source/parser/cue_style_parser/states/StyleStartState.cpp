#include "parser/cue_style_parser/states/StyleStartState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/webvtt_objects/RegionStyleSheet.hpp"
#include "elements/webvtt_objects/CueStyleSheet.hpp"
#include "elements/style_selectors/MatchAllSelector.hpp"
#include "exceptions/styleParserExceptions/StyleSheetFormatError.hpp"

namespace webvtt {

StyleSheet::StyleSheetType StyleStartState::decideStyleSheetType(std::u32string_view input) {
  bool isCue = (StyleSheetParser::CUE_STYLE_START == input);
  bool isCueRegion = (StyleSheetParser::REGION_STYLE_START == input);

  if (isCue)
    return StyleSheet::StyleSheetType::CUE;
  if (isCueRegion)
    return StyleSheet::StyleSheetType::REGION;

  return StyleSheet::StyleSheetType::UNDEFINED;
}

void StyleStartState::makeNewStyleSheetForParsing(StyleSheetParser &parser) {
  ParserUtil::strip(parser.getBuffer(), ParserUtil::isASCIIWhiteSpaceCharacter);
  auto type = decideStyleSheetType(parser.getBuffer());
  auto styleSheet = StyleSheet::makeNewStyleSheet(type);
  if (styleSheet == nullptr) {
    throw StyleSheetFormatError();
  }
  parser.setNewObjectForParsing(std::move(styleSheet));
  parser.getBuffer().clear();
}

void StyleStartState::processState(StyleSheetParser &parser) {
  uint32_t character = getNextCharacter(parser);

  switch (character) {
    case ParserUtil::SOLIDUS_C:parser.saveStateBeforeComment();
      parser.setState(StyleState::StyleStateType::START_COMMENT_STATE);
      break;
    case ParserUtil::LEFT_PARENTHESIS_C: {
      try {
        parser.setState(StyleState::StyleStateType::START_SELECTOR);
        makeNewStyleSheetForParsing(parser);
      } catch (const StyleSheetFormatError &error) {
        parser.setState(StyleState::StyleStateType::ERROR);
        return;
      }
      break;
    }
    case ParserUtil::LEFT_CURLY_BRACKET_C:
    case ParserUtil::COMMA_C: {
      try {
        makeNewStyleSheetForParsing(parser);
        parser.addSelectorToCurrentCompoundSelectorList(std::make_unique<MatchAllSelector>());
        parser.addSelectorToCurrentCombinatorSelectorList();
        parser.getCurrentPosition()--;
        parser.setState(StyleState::StyleStateType::BEFORE_RULE_STATE);
      } catch (const StyleSheetFormatError &error) {
        parser.setState(StyleState::StyleStateType::ERROR);
        return;
      }
      break;
    }
    case StyleSheetParser::STOP_PARSER:ParserUtil::strip(parser.getBuffer(), ParserUtil::isASCIIWhiteSpaceCharacter);
      if (!parser.getBuffer().empty())
        parser.setState(StyleState::StyleStateType::ERROR);
      else
        parser.setState(StyleState::StyleStateType::END_STATE);
      break;

    default:parser.getBuffer().push_back(character);
      break;
  }
}
}