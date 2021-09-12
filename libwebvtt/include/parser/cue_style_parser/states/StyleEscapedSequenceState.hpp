#ifndef LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_STATES_STYLE_ESCAPED_SEQUENCE_STATE_HPP_
#define LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_STATES_STYLE_ESCAPED_SEQUENCE_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {

class StyleEscapedSequenceState : public StyleState {
 public:
  void processState(StyleSheetParser &parser) override;
};

}

#endif // LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_STATES_STYLE_ESCAPED_SEQUENCE_STATE_HPP_
