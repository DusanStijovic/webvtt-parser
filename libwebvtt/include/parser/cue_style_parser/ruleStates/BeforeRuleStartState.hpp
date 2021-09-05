#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_RULE_STATES_BEFORE_RULE_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_RULE_STATES_BEFORE_RULE_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {

class BeforeRuleStartState : public StyleState {
 public:
  BeforeRuleStartState() = default;
  void processState(StyleSheetParser &parser) override;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_RULE_STATES_BEFORE_RULE_STATE_HPP_