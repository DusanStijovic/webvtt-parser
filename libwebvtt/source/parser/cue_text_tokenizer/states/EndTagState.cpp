#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/cue_text_tokenizer/states/EndTagState.hpp"
#include "parser/cue_text_tokenizer/tokens/EndTagToken.hpp"
#include "parser/ParserUtil.hpp"
#include <memory>

namespace webvtt
{

    std::unique_ptr<Token> EndTagState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);

        switch (character)
        {
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];
        case CueTextTokenizer::STOP_TOKENIZER:
          return std::make_unique<EndTagToken>(tokenizer.getResult());
            break;
        default:
            tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
}