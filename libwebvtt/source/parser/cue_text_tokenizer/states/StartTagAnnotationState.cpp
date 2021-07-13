#include "parser/cue_text_tokenizer/states/StartTagAnnotationState.h"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"

namespace WebVTT
{

    std::shared_ptr<Token> StartTagAnnotationState::process()
    {
        uint32_t character = *this->tokenizer.getCurrentPosition();

        switch (character)
        {
        case ParserUtil::AMPERSAND_C:
            //TODO Try to consume html charater reference
            break;
        case ParserUtil::HYPHEN_GREATER:
            this->tokenizer.getCurrentPosition()++;
        case CueTextTokenizer::STOP_TOKENIZER:
            ParserUtil::strip(this->tokenizer.getBuffer(), ParserUtil::isWhiteSpaceCharacter);
            ParserUtil::replaceAllSequenceWithOneCharacter(this->tokenizer.getBuffer(), ParserUtil::isWhiteSpaceCharacter);
            return std::make_shared<StartTagToken>(
                this->tokenizer.getResult(),
                this->tokenizer.getClasses(),
                this->tokenizer.getBuffer());
        default:
            this->tokenizer.getBuffer().push_back(character);
            break;
        }
        return nullptr;
    }

}