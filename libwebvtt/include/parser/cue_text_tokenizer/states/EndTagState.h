#ifndef LIBWEBVTT_ENDTAGSTATE_H
#define LIBWEBVTT_ENDTAGSTATE_H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{

    class EndTagState : public CueTextTokenizerState
    {

    public:
       EndTagState(CueTextTokenizer& tokenizer)
            : CueTextTokenizerState(tokenizer) {};
            virtual std::shared_ptr<Token> process() override;

    private:
    };
}

#endif //LIBWEBVTT_ENDTAGSTATE_H
