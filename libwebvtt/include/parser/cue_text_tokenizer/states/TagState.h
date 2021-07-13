#ifndef LIBWEBVTT_TAGSTATE_H
#define LIBWEBVTT_TAGSTATE_H
#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include <memory>

namespace WebVTT
{

    class TagState : public CueTextTokenizerState
    {
    public:
        TagState(CueTextTokenizer &tokenizer)
            : CueTextTokenizerState(tokenizer){};

        virtual std::shared_ptr<Token> process() override;


    };
}

#endif //LIBWEBVTT_TAGSTATE_H
