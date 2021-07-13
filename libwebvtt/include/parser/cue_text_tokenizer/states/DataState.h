#ifndef LIBWEBVTT_DATA_STATE_H
#define LIBWEBVTT_DATA_STATE_H

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include <memory>

namespace WebVTT
{

    class DataState : public CueTextTokenizerState
    {

    public:
        DataState(CueTextTokenizer &tokenizer)
            : CueTextTokenizerState(tokenizer){};
        virtual std::shared_ptr<Token> process() override;

    private:
    };
}

#endif
