#include "parser/cue_text_tokenizer/states/TimeStampTagState.hpp"
#include "parser/cue_text_tokenizer/tokens/TimeStampTagToken.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt
{
    std::unique_ptr<Token> TimpStampTagState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);
        switch (character)
        {
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];
        case CueTextTokenizer::STOP_TOKENIZER:
          return std::make_unique<TimeStampTagToken>(tokenizer.getResult());

        default:
            tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
} // namespace webvtt
