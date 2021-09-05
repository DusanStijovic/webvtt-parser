#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_RULE_STATES_STYLE_RULES_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_RULE_STATES_STYLE_RULES_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"
#include "utf8.h"
#include <string>
#include <set>

namespace webvtt {

class StyleRulesState : public StyleState {
 public:
  StyleRulesState() = default;
  void processState(StyleSheetParser &parser) override;

 private:
  void processRule(StyleSheetParser &parser, std::u32string_view input);

 private:
};
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_RULE_STATES_STYLE_RULES_STATE_HPP_
