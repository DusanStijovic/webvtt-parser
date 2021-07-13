#include "parser/cue_text_tokenizer/states/TimeStampTagState.h"
#include "parser/cue_text_tokenizer/tokens/TimeStampTagToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{
    std::shared_ptr<Token> TimpStampTagState::process()
    {
        uint32_t character = *this->tokenizer.getCurrentPosition();
        switch (character)
        {
        case ParserUtil::HYPHEN_GREATER:
            this->tokenizer.getCurrentPosition()++;
        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<TimeStampTagToken>(this->tokenizer.getResult());

        default:
            this->tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
} // namespace WebVTT
