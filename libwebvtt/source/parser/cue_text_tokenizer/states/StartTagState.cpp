#include "parser/cue_text_tokenizer/states/StartTagState.h"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.h"
#include "parser/cue_text_tokenizer/tokens/Token.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT
{
    std::shared_ptr<Token> StartTagState::process()
    {
        uint32_t character = *tokenizer.getCurrentPosition();
        switch (character)
        {
        case ParserUtil::TAB_C:
        case ParserUtil::FF_C:
        case ParserUtil::SPACE_C:
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::LF_C:
            this->tokenizer.getBuffer().clear();
            this->tokenizer.getBuffer().push_back(character);
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::FULL_STOP:
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_CLASS);

        case ParserUtil::HYPHEN_GREATER:
            this->tokenizer.getCurrentPosition()++;
            break;

        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<StartTagToken>(this->tokenizer.getResult());

        default:
            this->tokenizer.getResult().push_back(character);
            break;
        }
        return nullptr;
    }
}