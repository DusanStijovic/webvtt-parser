#ifndef LIBWEBVTT_TOKEN_H
#define LIBWEBVTT_TOKEN_H
#include "elements/cue_nodes/NodeObject.h"
#include <string>
#include <stack>
#include <memory>

namespace WebVTT
{

    class Token
    {
    public:
        Token(std::u32string &tokenValue) : tokenValue(tokenValue) {}

        virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language) = 0;

    protected:
        std::u32string tokenValue;
    };

}

#endif //LIBWEBVTT_TOKEN_H
