#include "parser/cue_text_tokenizer/states/TagState.h"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    std::shared_ptr<Token> TagState::process()
    {
        uint32_t character = *this->tokenizer.getCurrentPosition();

        if (ParserUtil::isDigit(character))
        {
            this->tokenizer.getResult().clear();
            this->tokenizer.getResult().push_back(character);
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG);
            return nullptr;
        }

        switch (character)
        {
        case ParserUtil::TAB_C:
        case ParserUtil::LF_C:
        case ParserUtil::FF_C:
        case ParserUtil::SPACE_C:
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::FULL_STOP:
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_CLASS);
            break;
        case ParserUtil::SOLIDUS_C:
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::END_TAG);

        case ParserUtil::HYPHEN_GREATER:
            this->tokenizer.getCurrentPosition()++;

        case CueTextTokenizer::STOP_TOKENIZER:
            return std::make_shared<StartTagToken>(this->tokenizer.getResult());
        default:
            this->tokenizer.getResult().clear();
            this->tokenizer.getResult().push_back(character);
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG);
            break;
        }
        return nullptr;
    }

}
