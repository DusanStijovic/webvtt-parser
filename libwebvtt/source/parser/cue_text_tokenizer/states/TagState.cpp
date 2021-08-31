#include "parser/cue_text_tokenizer/states/TagState.h"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    std::shared_ptr<Token> TagState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);
        if (ParserUtil::isAsciiDecDigit(character))
        {
            tokenizer.getResult().clear();
            tokenizer.getResult().push_back(character);
          tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG);
            return nullptr;
        }

        switch (character)
        {
        case ParserUtil::TAB_C:
        case ParserUtil::LF_C:
        case ParserUtil::FF_C:
        case ParserUtil::SPACE_C:tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::FULL_STOP:tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_CLASS);
            break;

        case ParserUtil::SOLIDUS_C:tokenizer.setState(CueTextTokenizerState::TokenizerState::END_TAG);
            break;

        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];
        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<StartTagToken>(tokenizer.getResult());
        default:
            tokenizer.getResult().clear();
            tokenizer.getResult().push_back(character);
            tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG);
            break;
        }
        return nullptr;
    }

}
