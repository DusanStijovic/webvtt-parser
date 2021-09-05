#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_DATA_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_DATA_STATE_HPP_
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"
#include <memory>

namespace webvtt
{

    class DataState : public CueTextTokenizerState
    {

    public:
        DataState() = default;
        virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) override;

    private:
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_DATA_STATE_HPP_
