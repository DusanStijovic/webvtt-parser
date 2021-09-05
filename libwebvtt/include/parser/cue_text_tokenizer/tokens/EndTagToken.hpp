#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_END_TAG_TOKEN_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_END_TAG_TOKEN_HPP_
#include "Token.hpp"
#include <string>

namespace webvtt
{

    class EndTagToken : public Token
    {

    public:
        EndTagToken(std::u32string &tokenValue) : Token(tokenValue)
        {
        }
        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_END_TAG_TOKEN_HPP_
