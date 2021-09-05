#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_TIME_STAMP_TAG_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_TIME_STAMP_TAG_STATE_HPP_
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"

namespace webvtt
{
    class TimpStampTagState : public CueTextTokenizerState
    {
    public:
        TimpStampTagState() = default;
        virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) override;

    private:
    };
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_TIME_STAMP_TAG_STATE_HPP_
