#ifndef LIBWEBVTT_START_TAG_TOKEN_H
#define LIBWEBVTT_START_TAG_TOKEN_H

#include "parser/cue_text_tokenizer/tokens/Token.h"
#include <string>
#include <list>

namespace WebVTT
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

#endif //LIBWEBVTT_START_TAG_TOKEN_H
