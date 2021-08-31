#include "parser/cue_text_tokenizer/states/TimeStampTagState.h"
#include "parser/cue_text_tokenizer/tokens/TimeStampTagToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{
    std::shared_ptr<Token> TimpStampTagState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);
        switch (character)
        {
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];
        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<TimeStampTagToken>(tokenizer.getResult());

        default:
            tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
} // namespace WebVTT
