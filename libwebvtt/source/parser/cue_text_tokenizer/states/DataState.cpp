#include "parser/cue_text_tokenizer/states/DataState.h"
#include "parser/cue_text_tokenizer/states/TagState.h"
#include "parser/cue_text_tokenizer/tokens/BasicToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT
{

    std::shared_ptr<Token> DataState::process()
    {
        {
            uint32_t character = *this->tokenizer.getCurrentPosition();
            switch (character)
            {
            case ParserUtil::AMPERSAND_C:
            {
                tokenizer.getCurrentPosition()++;
                std::u32string result = ParserUtil::consumeHTMLCharacter(tokenizer.getInput(), tokenizer.getCurrentPosition(), std::nullopt, false);
                if (result.empty())
                    tokenizer.getResult().push_back(ParserUtil::AMPERSAND_C);
                else
                    tokenizer.getResult().append(result);
                tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::DATA);
                break;
            }
            case ParserUtil::HYPHEN_LESS:
                if (tokenizer.getResult().empty())
                {
                    this->tokenizer.setTokenizerState(CueTextTokenizer::TokenizerState::START_TAG);
                }
                else
                {
                    return std::make_shared<BasicToken>(tokenizer.getResult());
                }

            case CueTextTokenizer::STOP_TOKENIZER:
                return std::make_shared<BasicToken>(tokenizer.getResult());
                break;
            default:
                tokenizer.getResult().push_back(character);
                break;
            }
        };
        return nullptr;
    }
}