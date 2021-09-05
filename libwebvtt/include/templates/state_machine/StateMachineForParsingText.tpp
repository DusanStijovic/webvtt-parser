namespace webvtt{

template<typename State, typename StateType>
void StateMachineForParsingText<State, StateType>::setText(std::u32string_view newInput) {
  {
    this->input = newInput;
    this->currentPosition = this->input.begin();
  }
}

template<typename State, typename StateType>
void StateMachineForParsingText<State, StateType>::setState(StateType newState) {
  currentState = State::getInstance(newState);
}

template<typename State, typename StateType>
const State *StateMachineForParsingText<State, StateType>::getState() const {
  return currentState;
}

}