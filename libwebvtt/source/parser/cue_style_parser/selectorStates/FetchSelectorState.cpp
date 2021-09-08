#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"
#include "parser/ParserUtil.hpp"
#include "exceptions/NotImplementedError.hpp"

namespace webvtt {

void FetchSelectorState::processState(StyleSheetParser &parser) {
  uint32_t character = getNextCharacter(parser);
  bool processDone = additionalBehaviour(parser, character);

  StyleSelector::StyleSelectorCombinator combinator = StyleSelector::StyleSelectorCombinator::NONE;

  if (processDone)
    return;

  switch (character) {
    case ParserUtil::LF_C:
    case ParserUtil::TAB_C:
    case ParserUtil::SPACE_C:combinator = StyleSelector::StyleSelectorCombinator::DESCENDANT;
      foundCombinatorCharacter(parser, combinator);
      break;
    case ParserUtil::PLUS_SIGN_C:combinator = StyleSelector::StyleSelectorCombinator::NEXT_SIBLING;
      foundCombinatorCharacter(parser, combinator);
      break;
    case ParserUtil::HYPHEN_GREATER:combinator = StyleSelector::StyleSelectorCombinator::CHILD;
      foundCombinatorCharacter(parser, combinator);
      break;
    case ParserUtil::TILDE_C:combinator = StyleSelector::StyleSelectorCombinator::SUBSEQUENT_SIBLING;
      foundCombinatorCharacter(parser, combinator);
      break;

    case ParserUtil::HASHTAG_C:
    case ParserUtil::COLON_C:
    case ParserUtil::DOT_C:foundCompoundCharacter(parser);
      break;

    case ParserUtil::COMMA_C:foundCommaCharacter(parser);
      break;

    case ParserUtil::RIGHT_PARENTHESIS_C:foundRightParenthesis(parser);
      break;

    case StyleSheetParser::STOP_PARSER:foundStopTokenizer(parser);
      break;

    default:foundDefaultBehaviour(parser, character);
      break;
  }
}

void FetchSelectorState::foundCommaCharacter(StyleSheetParser &parser,
                                             std::unique_ptr <StyleSelector> &&styleSelector) {

  parser.addSelectorToCurrentCompoundSelectorList(std::move(styleSelector));
  parser.addSelectorToCurrentCombinatorSelectorList();
  parser.goToSavedState();
}

void FetchSelectorState::foundCombinatorCharacter(StyleSheetParser &parser,
                                                  std::unique_ptr <StyleSelector> &&styleSelector) {
  parser.addSelectorToCurrentCompoundSelectorList(std::move(styleSelector));
  parser.addSelectorToCurrentCombinatorSelectorList();
}

void FetchSelectorState::foundCompoundCharacter(StyleSheetParser &parser,
                                                std::unique_ptr <StyleSelector> &&styleSelector) {
  parser.addSelectorToCurrentCompoundSelectorList(std::move(styleSelector));
  parser.goToSavedState();
  parser.getCurrentPosition()--;
}

void FetchSelectorState::foundRightParenthesis(StyleSheetParser &parser,
                                               std::unique_ptr <StyleSelector> &&styleSelector) {
  parser.addSelectorToCurrentCompoundSelectorList(std::move(styleSelector));
  parser.addSelectorToCurrentCombinatorSelectorList();
  parser.addSelectorToCurrentObject();
  parser.setState(StyleState::StyleStateType::END_SELECTOR);
  parser.getCurrentPosition()--;
}

void FetchSelectorState::foundStopTokenizer(StyleSheetParser &parser) {
  parser.setState(StyleState::StyleStateType::ERROR);
}

void FetchSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) {
  parser.getBuffer().push_back(character);
};

bool FetchSelectorState::additionalBehaviour(StyleSheetParser &parser, uint32_t character) {

  if (escapedSequence) {

    //Escape one css special character, need to be immediately after backslash.
    if (counterOfEscapedSequence == 0) {
      if (!ParserUtil::isAsciiHexDigit(character) &&
          ParserUtil::CR_C != character && ParserUtil::LF_C != character && ParserUtil::FF_C != character) {
        escapedSequence = false;
        parser.getBuffer().push_back(character);
        return true;
      }
    }

    //Multiple character, all need to be hexadecimal
    if (counterOfEscapedSequence >= ParserUtil::MAX_NUMBER_OF_CSS_ESCAPED_CHARACTER ||
        !ParserUtil::isAsciiHexDigit(character) || ParserUtil::isASCIIWhiteSpaceCharacter(character)
        ) {
      escapedSequence = false;
      counterOfEscapedSequence = 0;

      //First space after escaped sequence need to be skipped
      if (ParserUtil::isASCIIWhiteSpaceCharacter(character)) {
        parser.getBuffer().push_back(character);
        return true;
      } else
        return false;
    } else {
      counterOfEscapedSequence++;
      parser.getBuffer().push_back(character);
      return true;
    }
  } else {

    if (ParserUtil::BACK_SLASH_C == character) {
      escapedSequence = true;
      counterOfEscapedSequence = 0;
      parser.getBuffer().push_back(character);
      return true;
    } else {
      return false;
    }
  }
}

void FetchSelectorState::foundCombinatorCharacter(StyleSheetParser &parser,
                                                  StyleSelector::StyleSelectorCombinator styleCombinator) {
  DILOGI("COMBINATOR SELECTORS MATCHING NOT IMPLEMENTED");
  throw NotImplementedError();
  preprocessBuffer(parser);
  foundCombinatorCharacter(parser, makeNewStyleSelector(parser));
  parser.setCombinatorToMostRecentSelector(styleCombinator);
};

void FetchSelectorState::foundCompoundCharacter(StyleSheetParser &parser) {
  DILOGI("COMPOUND SELECTORS MATCHING NOT IMPLEMENTED");
  throw NotImplementedError();
  preprocessBuffer(parser);
  foundCompoundCharacter(parser, makeNewStyleSelector(parser));
};

void FetchSelectorState::foundRightParenthesis(StyleSheetParser &parser) {
  preprocessBuffer(parser);
  foundRightParenthesis(parser, makeNewStyleSelector(parser));
  parser.setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator::NONE);
  parser.addCurrentObjectToStyleSheetList();
};

void FetchSelectorState::foundCommaCharacter(StyleSheetParser &parser) {
  DILOGI("MULTIPLE SELECTORS MATCHING NOT IMPLEMENTED");
  throw NotImplementedError();
  preprocessBuffer(parser);
  foundCommaCharacter(parser, makeNewStyleSelector(parser));
  parser.setCombinatorToMostRecentSelector(StyleSelector::StyleSelectorCombinator::MULTIPLE);
}

} // namespace webvtt
