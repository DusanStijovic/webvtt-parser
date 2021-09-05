#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_TIME_STAMP_TAG_TOKEN_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_TIME_STAMP_TAG_TOKEN_HPP_
#include "parser/cue_text_tokenizer/tokens/Token.hpp"
#include <string>

namespace webvtt
{

    class TimeStampTagToken : public Token
    {
    public:
        TimeStampTagToken(std::u32string &tagName) : Token(tagName)
        {
        }
        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_TIME_STAMP_TAG_TOKEN_HPP_
