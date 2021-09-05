#ifndef CUE_TEXT_TOKENIZER_EXCEPTION_H
#define CUE_TEXT_TOKENIZER_EXCEPTION_H
#include <exception>

class CueTextTokenizerException : public std::excpetions
{
public:
    virtual const char *what() const override
    {
        return "Error while parsing cue styling text";
    }
}

#endif