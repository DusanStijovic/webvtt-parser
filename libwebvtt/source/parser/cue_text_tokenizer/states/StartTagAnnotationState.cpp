#include "parser/cue_text_tokenizer/states/StartTagAnnotationState.hpp"
#include "parser/cue_text_tokenizer/tokens/StartTagToken.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt
{

    std::unique_ptr<Token> StartTagAnnotationState::process(CueTextTokenizer &tokenizer)
    {
        uint32_t character = getNextCharacter(tokenizer);
        switch (character)
        {
        case ParserUtil::AMPERSAND_C:
        {
            bool parsingError = false;
            tokenizer.getCurrentPosition()++;
            std::u32string result = ParserUtil::consumeHTMLCharacter(tokenizer.getInput(),
                                                                     tokenizer.getCurrentPosition(),
                                                                     ParserUtil::HYPHEN_LESS, true, parsingError);
            if (result.empty())
                tokenizer.getResult().push_back(ParserUtil::AMPERSAND_C);
            else
                tokenizer.getResult().append(result);
          tokenizer.setState(CueTextTokenizerState::TokenizerState::START_TAG_ANNOTATION);
            break;
        }
        case ParserUtil::HYPHEN_GREATER:
            tokenizer.getCurrentPosition()++;
            [[fallthrough]];
        case CueTextTokenizer::STOP_TOKENIZER:
        {
            std::u32string_view temp = tokenizer.getBuffer();
            ParserUtil::strip(temp, ParserUtil::isASCIIWhiteSpaceCharacter);
            tokenizer.getBuffer() = std::u32string(temp);

            ParserUtil::replaceAllSequenceOfCharactersWithGivenCharacter(tokenizer.getBuffer(), ParserUtil::isASCIIWhiteSpaceCharacter, ParserUtil::SPACE_C);

            return std::make_unique<StartTagToken>(
                tokenizer.getResult(),
                tokenizer.getClasses(),
                tokenizer.getBuffer());
            break;
        }
        default:
            tokenizer.getBuffer().push_back(character);
            break;
        }
        return nullptr;
    }

}