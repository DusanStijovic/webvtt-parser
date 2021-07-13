#ifndef LIBWEBVTT_BASIC_TOKEN_H
#define LIBWEBVTT_BASIC_TOKEN_H
#include "Token.h"
#include <string>

namespace WebVTT
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

#endif
