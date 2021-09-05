#ifndef LIBWEBVTT_CUE_PARSING_TIMING_EXCEPTION_H
#define LIBWEBVTT_CUE_PARSING_TIMING_EXCEPTION_H
#include <exception>

class CueParsingTimingException : public std::exception
{
public:
  const char *what() const noexcept override
  {
    return "Error while parsing cue timing";
  }
};

#endif //LIBWEBVTT_CUE_PARSING_TIMING_EXCEPTION_H
