#ifndef LIBWEBVTT_STARTTAGSTATE_H
#define LIBWEBVTT_STARTTAGSTATE_H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{
    class StartTagState : public CueTextTokenizerState
    {
    public:
        StartTagState(CueTextTokenizer &tokenizer)
            : CueTextTokenizerState(tokenizer) {};
           virtual std::shared_ptr<Token> process() override;

    private:
    };
}

#endif //LIBWEBVTT_STARTTAGSTATE_H
