#ifndef LIBWEBVTT_INCLUDE_EXCEPTIONS_NOT_IMPLEMENTED_ERROR_HPP_
#define LIBWEBVTT_INCLUDE_EXCEPTIONS_NOT_IMPLEMENTED_ERROR_HPP_
#include <exception>

namespace webvtt {
class NotImplementedError : public std::exception {
 public:
  [[nodiscard]] const char *what() const noexcept override {
    return "Not implemented exception";
  }

};
}
#endif // LIBWEBVTT_INCLUDE_EXCEPTIONS_NOT_IMPLEMENTED_ERROR_HPP_
