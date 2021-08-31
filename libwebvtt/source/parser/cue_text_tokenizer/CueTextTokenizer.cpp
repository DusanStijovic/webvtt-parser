#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/cue_text_tokenizer/tokens/Token.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT {

std::shared_ptr<Token> CueTextTokenizer::getNextToken() {
  buffer.clear();
  result.clear();
  classes.clear();
  setState(CueTextTokenizerState::TokenizerState::DATA);

  while (true) {
    std::shared_ptr<Token> token = currentState->process(*this);
    if (token != nullptr)
      return token;
    currentPosition++;
  }
}


}
