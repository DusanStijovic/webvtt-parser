#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_ANNOTATION_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_ANNOTATION_STATE_HPP_
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"

namespace webvtt
{

    class StartTagAnnotationState : public CueTextTokenizerState
    {
    public:
        StartTagAnnotationState() = default;
        virtual std::unique_ptr<Token> process(CueTextTokenizer &tokenizer) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_STATES_START_TAG_ANNOTATION_STATE_HPP_
