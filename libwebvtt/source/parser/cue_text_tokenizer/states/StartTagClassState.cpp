#include "parser/cue_text_tokenizer/states/StartTagClassState.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt
{

    std::unique_ptr<Token> StartTagClassState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);
        switch (character)
        {
        case ParserUtil::TAB_C:
        case ParserUtil::FF_C:
        case ParserUtil::SPACE_C:
            DILOGI(utf8::utf32to8(tokenizer.getBuffer()));
            tokenizer.addBufferToClasses();
            tokenizer.getBuffer().clear();
            tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::LF_C:
            DILOGI(utf8::utf32to8(tokenizer.getBuffer()));
            tokenizer.addBufferToClasses();
            ParserUtil::clearAndSetCharacter(tokenizer.getBuffer(), character);
            tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_ANNOTATION);
            break;

        case ParserUtil::FULL_STOP:
            DILOGI(utf8::utf32to8(tokenizer.getBuffer()));
            tokenizer.addBufferToClasses();
            tokenizer.getBuffer().clear();
            break;
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];

        case CueTextTokenizer::STOP_TOKENIZER:
            DILOGI(utf8::utf32to8(tokenizer.getBuffer()));
            tokenizer.addBufferToClasses();
            return std::make_unique<StartTagToken>(
                tokenizer.getResult(),
                tokenizer.getClasses());
            break;
        default:
            tokenizer.getBuffer().push_back(character);
            break;
        }
        return nullptr;
    }

}