#ifndef LIBWEBVTT_ENDTAGSTATE_H
#define LIBWEBVTT_ENDTAGSTATE_H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"

namespace WebVTT
{

    class EndTagState : public CueTextTokenizerState
    {

    public:
        EndTagState() = default;
        virtual std::shared_ptr<Token> process(CueTextTokenizer &tokenizer) override;

    private:
    };
}

#endif //LIBWEBVTT_ENDTAGSTATE_H
