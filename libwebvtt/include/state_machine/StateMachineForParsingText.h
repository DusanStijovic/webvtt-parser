#ifndef STATE_MACHINE_FOR_PARSING_TEXT_H
#define STATE_MACHINE_FOR_PARSING_TEXT_H
#include <string>

namespace WebVTT {
template<typename State, typename StateType>
class StateMachineForParsingText {

 public:

  void setState(StateType newState);
  const State *getState() const;

  void setText(std::u32string_view input);
  inline std::u32string_view getInput() { return input; }
  inline std::u32string_view::iterator &getCurrentPosition() { return currentPosition; }

 protected:
  State *currentState;
  std::u32string_view input{};
  std::u32string_view::iterator currentPosition{};
};
} // namespace WebVTT

#include "templates/state_machine/StateMachineForParsingText.tpp"
#endif //STATE_MACHINE_FOR_PARSING_TEXT_H