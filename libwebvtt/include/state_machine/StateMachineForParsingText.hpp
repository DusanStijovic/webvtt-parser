#ifndef LIBWEBVTT_INCLUDE_STATE_MACHINE_FOR_PARSING_TEXT_HPP_
#define LIBWEBVTT_INCLUDE_STATE_MACHINE_FOR_PARSING_TEXT_HPP_
#include <string>

namespace webvtt {
template<typename State, typename StateType>
class StateMachineForParsingText {

 public:

  void setState(StateType newState);
  const State *getState() const;

  void setText(std::u32string_view input);
  inline std::u32string_view getInput() { return input; }
  inline std::u32string_view::iterator &getCurrentPosition() { return currentPosition; }

  StateMachineForParsingText() = default;
  StateMachineForParsingText(const StateMachineForParsingText &) = delete;
  StateMachineForParsingText(StateMachineForParsingText &&) = delete;
  StateMachineForParsingText &operator=(const StateMachineForParsingText &) = delete;
  StateMachineForParsingText &operator=(StateMachineForParsingText &&) = delete;
  virtual ~StateMachineForParsingText() = default;

 protected:
  State *currentState;
  std::u32string_view input{};
  std::u32string_view::iterator currentPosition{};
};
} // namespace webvtt

#include "templates/state_machine/StateMachineForParsingText.tpp"
#endif // LIBWEBVTT_INCLUDE_STATE_MACHINE_FOR_PARSING_TEXT_HPP_