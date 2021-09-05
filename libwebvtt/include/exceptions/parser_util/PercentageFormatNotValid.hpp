#ifndef LIBWEBVTT_INCLUDE_EXCEPTIONS_PARSER_UTIL_PERCENTAGE_FORMAT_NOT_VALID_H
#define LIBWEBVTT_INCLUDE_EXCEPTIONS_PARSER_UTIL_PERCENTAGE_FORMAT_NOT_VALID_H
#include <exception>

class PercentageFormatNotValid : public std::exception {

 public:
  const char *what() const noexcept override {
    return "Percentage format not valid";
  }
};

#endif //LIBWEBVTT_INCLUDE_EXCEPTIONS_PARSER_UTIL_PERCENTAGE_FORMAT_NOT_VALID_H
