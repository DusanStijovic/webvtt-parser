#ifndef PARSING_INTEGER_NUMBER_H
#define PARSING_INTEGER_NUMBER_H
#include <exception>

class ParsingLongNumberError : public std::exception
{
public:
    [[nodiscard]] const char *what() const noexcept override
    {
        return "Error while parsing integer number";
    }
};

#endif // PARSING_INTEGER_NUMBER_H