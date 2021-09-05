#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_TAG_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_TAG_STATE_HPP_
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"
#include <memory>

namespace webvtt
{

    class TagState : public CueTextTokenizerState
    {
    public:
        TagState() = default;

        virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) override;
    };
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_TAG_STATE_HPP_
