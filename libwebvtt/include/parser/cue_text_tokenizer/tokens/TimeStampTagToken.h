#ifndef LIBWEBVTT_TIME_STAMP_TAG_TOKEN_H
#define LIBWEBVTT_TIME_STAMP_TAG_TOKEN_H
#include "parser/cue_text_tokenizer/tokens/Token.h"
#include <string>

namespace WebVTT
{

    class TimeStampTagToken : public Token
    {
    public:
        TimeStampTagToken(std::u32string &tagName) : Token(tokenValue)
        {
        }
        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language) override;
    };

}
#endif
