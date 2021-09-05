#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_CUE_TEXT_TOKENIZER_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_CUE_TEXT_TOKENIZER_HPP_

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"
#include "parser/cue_text_tokenizer/tokens/Token.hpp"
#include "state_machine/StateMachineForParsingText.hpp"
#include <string>
#include <list>

namespace webvtt {

class CueTextTokenizer : public StateMachineForParsingText<CueTextTokenizerState,
                                                           CueTextTokenizerState::TokenizerState> {
 public:
  constexpr static uint32_t STOP_TOKENIZER = 0xFFFF;

  explicit CueTextTokenizer() {
    currentState = CueTextTokenizerState::getInstance(CueTextTokenizerState::TokenizerState::DATA);
  }
  std::unique_ptr<Token> getNextToken();

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

} // namespace webvtt
#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_CUE_TEXT_TOKENIZER_HPP_
