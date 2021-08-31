#ifndef PARSING_FLOAT_POINT_NUMBER_H
#define PARSING_FLOAT_POINT_NUMBER_H
#include <exception>

class ParsingFloatPointNumber : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error while parsing float point number";
    }
};

#endif