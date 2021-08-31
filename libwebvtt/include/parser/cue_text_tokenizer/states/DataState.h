#ifndef LIBWEBVTT_DATA_STATE_H
#define LIBWEBVTT_DATA_STATE_H

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include <memory>

namespace WebVTT
{

    class DataState : public CueTextTokenizerState
    {

    public:
        DataState() = default;
        virtual std::shared_ptr<Token> process(CueTextTokenizer &tokenizer) override;

    private:
    };
}

#endif
