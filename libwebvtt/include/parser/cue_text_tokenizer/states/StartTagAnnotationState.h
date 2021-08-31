#ifndef LIBWEBVTT_START_TAG_ANNOTATION_STATE_H
#define LIBWEBVTT_START_TAG_ANNOTATION_STATE_H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{

    class StartTagAnnotationState : public CueTextTokenizerState
    {
    public:
        StartTagAnnotationState() = default;
        virtual std::shared_ptr<Token> process(CueTextTokenizer &tokenizer) override;
    };
}

#endif
