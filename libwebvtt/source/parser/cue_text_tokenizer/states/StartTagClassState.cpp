#include "parser/cue_text_tokenizer/states/StartTagClassState.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    std::shared_ptr<Token> StartTagClassState::process()
    {
        uint32_t character = *this->tokenizer.getCurrentPosition();
        switch (character)
        {
        case ParserUtil::TAB_C:
        case ParserUtil::FF_C:
        case ParserUtil::SPACE_C:
            this->tokenizer.addBufferToClasses();
            this->tokenizer.getBuffer().clear();
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::LF_C:
            this->tokenizer.addBufferToClasses();
            ParserUtil::clearAndSetCharacter(this->tokenizer.getBuffer(), character);
            this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::FULL_STOP:
            this->tokenizer.addBufferToClasses();
            this->tokenizer.getBuffer().clear();
            break;
        case ParserUtil::HYPHEN_GREATER:
            this->tokenizer.getCurrentPosition()++;

        case CueTextTokenizer::STOP_TOKENIZER:
            this->tokenizer.addBufferToClasses();
            return std::make_shared<StartTagToken>(
                this->tokenizer.getResult(),
                this->tokenizer.getClasses());
            break;
        default:
            this->tokenizer.getBuffer().push_back(character);
            break;
        }
        return nullptr;
    }

}