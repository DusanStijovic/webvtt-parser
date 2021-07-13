#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/cue_text_tokenizer/states/EndTagState.h"
#include "parser/cue_text_tokenizer/tokens/EndTagToken.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT
{

    std::shared_ptr<Token> EndTagState::process()
    {
        uint32_t character = *tokenizer.getCurrentPosition();
        switch (character)
        {
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<EndTagToken>(this->tokenizer.getResult());
            break;
        default:
            tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
}