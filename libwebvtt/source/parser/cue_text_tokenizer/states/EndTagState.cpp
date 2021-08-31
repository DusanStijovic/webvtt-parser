#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/cue_text_tokenizer/states/EndTagState.h"
#include "parser/cue_text_tokenizer/tokens/EndTagToken.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT
{

    std::shared_ptr<Token> EndTagState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);

        switch (character)
        {
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];
        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<EndTagToken>(tokenizer.getResult());
            break;
        default:
            tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
}