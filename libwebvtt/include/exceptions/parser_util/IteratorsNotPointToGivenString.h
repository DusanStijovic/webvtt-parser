#ifndef ITERATORS_NOT_POINT_TO_GIVEN_STRING_H
#define ITERATORS_NOT_POINT_TO_GIVEN_STRING_H
#include <exception>

class IteratorsNotPointToGivenString : public std::exception
{
public:
    const char *what() const noexcept
    {
        return "Given iterator not point to given string";
    }
};

#endif