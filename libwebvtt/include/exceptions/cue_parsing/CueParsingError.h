#ifndef CUE_PARSING_ERROR_H
#define CUE_PARSING_ERROR_H
#include <exception>

class CueParsingError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error while parsing cue";
    }
};

#endif // CUE_PARSING_ERROR_H