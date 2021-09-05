#ifndef LIBWEBVTT_PARSING_TIME_STAMP_EXCEPTION_H
#define LIBWEBVTT_PARSING_TIME_STAMP_EXCEPTION_H

#include <exception>

class ParsingTimeStampException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Exception while parsing timestamp";
    }
};

#endif //LIBWEBVTT_PARSING_TIME_STAMP_EXCEPTION_H
