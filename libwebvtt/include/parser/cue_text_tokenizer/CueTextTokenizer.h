#ifndef LIBWEBVTT_CUE_TEXT_TOKENIZER_H
#define LIBWEBVTT_CUE_TEXT_TOKENIZER_H

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include "parser/cue_text_tokenizer/tokens/Token.h"
#include "state_machine/StateMachineForParsingText.h"
#include <string>
#include <list>

namespace WebVTT {

class CueTextTokenizer : public StateMachineForParsingText<CueTextTokenizerState,
                                                           CueTextTokenizerState::TokenizerState> {
 public:
  constexpr static uint32_t STOP_TOKENIZER = 0xFFFF;

  explicit CueTextTokenizer() {
    currentState = CueTextTokenizerState::getInstance(CueTextTokenizerState::TokenizerState::DATA);
  }
  std::shared_ptr<Token> getNextToken();


  inline std::u32string &getResult() { return result; }

  inline std::u32string &getBuffer() { return buffer; }

  inline std::list<std::u32string> &getClasses() { return classes; }

  void addBufferToClasses() {
    if (!this->buffer.empty())
      this->classes.push_back(this->buffer);
  }

 private:
  std::u32string buffer;

  std::u32string result;
  std::list<std::u32string> classes;
};

}
#endif
