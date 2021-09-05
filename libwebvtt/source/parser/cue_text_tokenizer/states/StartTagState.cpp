#include "parser/cue_text_tokenizer/states/StartTagState.hpp"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.hpp"
#include "parser/cue_text_tokenizer/tokens/Token.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/ParserUtil.hpp"
#include <memory>

namespace webvtt {
std::unique_ptr<Token> StartTagState::process(CueTextTokenizer &tokenizer) {
  uint32_t character = getNextCharacter(tokenizer);
  switch (character) {
    case ParserUtil::TAB_C:
    case ParserUtil::FF_C:
    case ParserUtil::SPACE_C:tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_ANNOTATION);
      break;

    case ParserUtil::LF_C:ParserUtil::clearAndSetCharacter(tokenizer.getBuffer(), character);
      tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_ANNOTATION);
      break;

    case ParserUtil::FULL_STOP:tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_CLASS);
      break;

    case ParserUtil::HYPHEN_GREATER:tokenizer.getCurrentPosition()++;
      [[fallthrough]];
    case CueTextTokenizer::STOP_TOKENIZER:return std::make_unique<StartTagToken>(tokenizer.getResult());
      break;
    default:tokenizer.getResult().push_back(character);
      break;
  }
  return nullptr;
}
}