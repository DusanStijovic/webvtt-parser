#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_CUE_STATES_START_CUE_STYLE_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_CUE_STATES_START_CUE_STYLE_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {

class StyleStartSelectorState : public StyleState {
 public:
  StyleStartSelectorState() = default;
  void processState(StyleSheetParser &parser) override;
};

}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_CUE_STATES_START_CUE_STYLE_SELECTOR_STATE_HPP_
