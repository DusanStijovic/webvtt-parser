#ifndef LIBWEBVTT_CUE_TEXT_TOKENIZER_STATE_H
#define LIBWEBVTT_CUE_TEXT_TOKENIZER_STATE_H
#include "parser/cue_text_tokenizer/tokens/Token.h"

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include <memory>
#include <string>
#include <map>

namespace WebVTT
{

    class CueTextTokenizer;

    class CueTextTokenizerState
    {

    public:
        virtual std::shared_ptr<Token> process() = 0;
        virtual std::shared_ptr<Token> getTokenOrNullptr();
        virtual ~CueTextTokenizerState() = default;

        explicit CueTextTokenizerState(CueTextTokenizer &tokenizer)
            : tokenizer(tokenizer){};

    protected:
        CueTextTokenizer &tokenizer;

        std::shared_ptr<Token> token = nullptr;

    private:
    };

}
#endif
