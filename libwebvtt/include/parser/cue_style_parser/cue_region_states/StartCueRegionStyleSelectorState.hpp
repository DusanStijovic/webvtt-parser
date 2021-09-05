#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_CUE_REGION_STATES_START_CUE_REGION_STYLE_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_CUE_REGION_STATES_START_CUE_REGION_STYLE_SELECTOR_STATE_HPP_

#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {
class StartCueRegionStyleSelectorState : public StyleState {
 public:
  StartCueRegionStyleSelectorState() = default;
  void processState(StyleSheetParser &parser) override;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_CUE_REGION_STATES_START_CUE_REGION_STYLE_SELECTOR_STATE_HPP_
