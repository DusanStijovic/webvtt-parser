#ifndef LIBWEBVTT_TIME_STAMP_TAG_STATE_H
#define LIBWEBVTT_TIME_STAMP_TAG_STATE _H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{
    class TimpStampTagState : public CueTextTokenizerState
    {
    public:
        TimpStampTagState() = default;
        virtual std::shared_ptr<Token> process(CueTextTokenizer &tokenizer) override;

    private:
    };
}

#endif
