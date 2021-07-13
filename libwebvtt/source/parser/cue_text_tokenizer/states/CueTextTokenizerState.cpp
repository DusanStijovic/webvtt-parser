#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{
    std::shared_ptr<Token> CueTextTokenizerState::getTokenOrNullptr()
    {
        return token;
    }
}
