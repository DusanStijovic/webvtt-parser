#ifndef LIBWEBVTT_END_TAG_TOKEN_H
#define LIBWEBVTT_END_TAG_TOKEN_H
#include "Token.h"
#include <string>

namespace WebVTT
{

    class EndTagToken : public Token
    {

    public:
        EndTagToken(std::u32string &tokenValue):Token(tokenValue)
        {
        }
        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages) override;
    };

}

#endif
