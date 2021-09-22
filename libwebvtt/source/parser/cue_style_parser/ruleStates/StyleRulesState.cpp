#include "parser/cue_style_parser/ruleStates/StyleRulesState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "logger/LoggingUtility.hpp"
#include <tuple>

namespace webvtt {

void StyleRulesState::processRule(StyleSheetParser &parser, std::u32string_view rule) {
  ParserUtil::strip(rule, ParserUtil::isASCIIWhiteSpaceCharacter);

  if (rule.empty())
    return;

  auto result = ParserUtil::splitStringAroundCharacter(rule, ParserUtil::COLON_C);
  if (result.has_value()) {
    auto name = std::get<0>(result.value());
    auto value = std::get<1>(result.value());
    ParserUtil::strip(name, ParserUtil::isASCIIWhiteSpaceCharacter);
    ParserUtil::strip(value, ParserUtil::isASCIIWhiteSpaceCharacter);

    parser.addCSSRule(utf8::utf32to8(name), utf8::utf32to8(value));
    parser.getBuffer().clear();
  } else {
    parser.setState(StyleState::StyleStateType::ERROR);
  }
}

void StyleRulesState::processState(StyleSheetParser &parser) {

  uint32_t character = getNextCharacter(parser);

  switch (character) {
    case ParserUtil::SOLIDUS_C:
      parser.saveStateBeforeComment();
      parser.setState(StyleState::StyleStateType::START_COMMENT_STATE);
      break;
    case ParserUtil::RIGHT_CURLY_BRACKET_C:parser.setState(StyleState::StyleStateType::START);
      break;
    case ParserUtil::SEMI_COLON:processRule(parser, parser.getBuffer());
      break;

    case StyleSheetParser::STOP_PARSER:parser.setState(StyleState::StyleStateType::ERROR);
      break;

    default:parser.getBuffer().push_back(character);
      break;
  }
}
} // namespace webvtt
