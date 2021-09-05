#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_CLASS_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_CLASS_STATE_HPP_s
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"

namespace webvtt
{

    class StartTagClassState : public CueTextTokenizerState
    {
    public:
        StartTagClassState() = default;
        virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) override;
    };

} // namespace

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_CLASS_STATE_HPP_
