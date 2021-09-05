#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/cue_text_tokenizer/tokens/Token.hpp"
#include "parser/ParserUtil.hpp"
#include <memory>

namespace webvtt {

std::unique_ptr<Token> CueTextTokenizer::getNextToken() {
  buffer.clear();
  result.clear();
  classes.clear();
  setState(CueTextTokenizerState::TokenizerState::DATA);

  while (true) {
    std::unique_ptr<Token> token = currentState->process(*this);
    if (token != nullptr)
      return token;
    currentPosition++;
  }
}


}
