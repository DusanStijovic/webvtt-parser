#ifndef LIBWEBVTT_INCLUDE_EXCEPTIONS_PARSER_UTIL_COLLECTING_CHARACTERS_EXCEPTION_H_
#define LIBWEBVTT_INCLUDE_EXCEPTIONS_PARSER_UTIL_COLLECTING_CHARACTERS_EXCEPTION_H_
#include <exception>

class CollectingCharactersException : public std::exception {
 public:
  const char *what() const noexcept override {
    return "Error while colleting characters, given position not ok";
  }
};

#endif //LIBWEBVTT_INCLUDE_EXCEPTIONS_PARSER_UTIL_COLLECTING_CHARACTERS_EXCEPTION_H_
