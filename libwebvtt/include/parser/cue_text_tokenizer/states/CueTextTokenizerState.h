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
        enum class TokenizerState
        {
            DATA,
            START_TAG,
            START_TAG_ANNOTATION,
            START_TAG_CLASS,
            END_TAG,
            TIME_STAMP_TAG,
            TAG
        };

        virtual std::shared_ptr<Token> process(CueTextTokenizer &tokenizer) = 0;

        uint32_t getNextCharacter(CueTextTokenizer &tokenizer);

        explicit CueTextTokenizerState() = default;
        virtual ~CueTextTokenizerState() = default;

        static CueTextTokenizerState *getInstance(CueTextTokenizerState::TokenizerState tokenizerState);

    private:
        static std::map<TokenizerState, std::unique_ptr<CueTextTokenizerState>> statesInstance;
        static std::unique_ptr<CueTextTokenizerState> makeNewTokenizerState(TokenizerState tokenizerState);
    };

}
#endif
