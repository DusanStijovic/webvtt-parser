#ifndef LIBWEBVTT_TIME_STAMP_TAG_STATE_H
#define LIBWEBVTT_TIME_STAMP_TAG_STATE _H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{
    class TimpStampTagState : public CueTextTokenizerState
    {
    public:
        TimpStampTagState(CueTextTokenizer &tokenizer)
            : CueTextTokenizerState(tokenizer){};
        virtual std::shared_ptr<Token> process() override;

    private:
    };
}

#endif
