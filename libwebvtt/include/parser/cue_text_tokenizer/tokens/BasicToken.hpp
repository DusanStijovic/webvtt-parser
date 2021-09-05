#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_BASIC_TOKEN_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_BASIC_TOKEN_HPP_
#include "Token.hpp"
#include <string>

namespace webvtt
{
    class BasicToken : public Token
    {
    public:
        BasicToken(std::u32string &tokenValue) : Token(tokenValue)
        {
        }
        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language) override;

    private:
    };
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_BASIC_TOKEN_HPP_
