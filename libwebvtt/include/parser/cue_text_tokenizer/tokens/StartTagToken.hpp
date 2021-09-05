#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_START_TAG_TOKEN_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_START_TAG_TOKEN_HPP_

#include "parser/cue_text_tokenizer/tokens/Token.hpp"
#include <string>
#include <list>

namespace webvtt
{

    class StartTagToken : public Token
    {
    public:
        StartTagToken(std::u32string &tokenValue, std::list<std::u32string> &classes,
                      std::u32string &annotations) : Token(tokenValue), classes(classes), annotations(annotations)
        {
        }

        StartTagToken(std::u32string &tokenValue, std::list<std::u32string> &classes) : Token(tokenValue),
                                                                                        classes(classes)
        {
        }

        explicit StartTagToken(std::u32string &tokenValue) : Token(tokenValue)
        {
        }
        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language) override;

    private:
        std::list<std::u32string> classes;
        std::u32string annotations;
    };
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_START_TAG_TOKEN_HPP_
