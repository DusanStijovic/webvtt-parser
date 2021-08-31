#ifndef PARSING_COORDINATES_H
#define PARSING_COORDINATES_H
#include <exception>

class ParsingCoordinatesError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Parsing coordinates error";
    }
};

#endif