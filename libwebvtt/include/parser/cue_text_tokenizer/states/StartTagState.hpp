#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_STATE_HPP_
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"

namespace webvtt
{
    class StartTagState : public CueTextTokenizerState
    {
    public:
        StartTagState() = default;
        virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) override;

    private:
    };
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_STATE_HPP_
