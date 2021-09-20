#include "parser/cue_text_tokenizer/states/TagState.hpp"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt
{

    std::unique_ptr<Token> TagState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);
        if (ParserUtil::isAsciiDecDigit(character))
        {
            tokenizer.getResult().clear();
            tokenizer.getResult().push_back(character);
          tokenizer.setState(CueTextTokenizerState::TokenizerState::TIME_STAMP_TAG);
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
          return std::make_unique<StartTagToken>(tokenizer.getResult());
        default:
            tokenizer.getResult().clear();
            tokenizer.getResult().push_back(character);
            tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG);
            break;
        }
        return nullptr;
    }

}
