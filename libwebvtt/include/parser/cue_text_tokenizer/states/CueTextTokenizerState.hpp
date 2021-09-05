#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_CUE_TEXT_TOKENIZER_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_CUE_TEXT_TOKENIZER_STATE_HPP_
#include "parser/cue_text_tokenizer/tokens/Token.hpp"

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"
#include <memory>
#include <string>
#include <map>

namespace webvtt
{

  class CueTextTokenizer;

  class CueTextTokenizerState
  {

  public:
    explicit CueTextTokenizerState() = default;
    CueTextTokenizerState(const CueTextTokenizerState &) = delete;
    CueTextTokenizerState(CueTextTokenizerState &&) = delete;
    CueTextTokenizerState &operator=(const CueTextTokenizerState &) = delete;
    CueTextTokenizerState &operator=(CueTextTokenizerState &&) = delete;
    virtual ~CueTextTokenizerState() = default;

    enum class TokenizerState
    {
      DATA,
      START_TAG,
      START_TAG_ANNOTATION,
      START_TAG_CLASS,
      END_TAG,
      TIME_STAMP_TAG,
      TAG
    };

    virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) = 0;

    uint32_t getNextCharacter(CueTextTokenizer &tokenizer);

    static CueTextTokenizerState *getInstance(CueTextTokenizerState::TokenizerState tokenizerState);

  private:
    static std::map<TokenizerState, std::unique_ptr<CueTextTokenizerState>> statesInstance;
    static std::unique_ptr<CueTextTokenizerState> makeNewTokenizerState(TokenizerState tokenizerState);
  };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_CUE_TEXT_TOKENIZER_STATE_HPP_
