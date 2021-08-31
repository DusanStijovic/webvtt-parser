#ifndef LIBWEBVTT_INCLUDE_EXCEPTIONS_STATE_MACHINE_STATE_MACHINE_IN_ERROR_STATE_H_
#define LIBWEBVTT_INCLUDE_EXCEPTIONS_STATE_MACHINE_STATE_MACHINE_IN_ERROR_STATE_H_
#include <exception>

class StateMachineInErrorState : public std::exception {
  const char *what() const noexcept {
    return "State machine in error state";
  }

};

#endif //LIBWEBVTT_INCLUDE_EXCEPTIONS_STATE_MACHINE_STATEMACHINEINERRORSTATE_H_
