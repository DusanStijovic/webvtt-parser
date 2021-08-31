#include "parser/cue_text_tokenizer/states/DataState.h"
#include "parser/cue_text_tokenizer/states/TagState.h"
#include "parser/cue_text_tokenizer/tokens/BasicToken.h"
#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT
{

    std::shared_ptr<Token> DataState::process(CueTextTokenizer &tokenizer)
    {
        {
            uint32_t character = getNextCharacter(tokenizer);
            switch (character)
            {
            case ParserUtil::AMPERSAND_C:
            {
                bool parsingError = false;
                std::u32string result = ParserUtil::consumeHTMLCharacter(tokenizer.getInput(),
                                                                         tokenizer.getCurrentPosition(),
                                                                         std::nullopt, false, parsingError);
                if (result.empty())
                    tokenizer.getResult().push_back(ParserUtil::AMPERSAND_C);
                else
                    tokenizer.getResult().append(result);
              tokenizer.setState(CueTextTokenizerState::TokenizerState::DATA);
                break;
            }
            case ParserUtil::HYPHEN_LESS:
                if (tokenizer.getResult().empty())
                {
                  tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG);
                }
                else
                {
                    return std::make_shared<BasicToken>(tokenizer.getResult());
                }
                break;
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