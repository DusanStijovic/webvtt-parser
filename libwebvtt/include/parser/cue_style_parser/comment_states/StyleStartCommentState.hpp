#ifndef LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_STATES_STYLE_START_COMMENT_STATE_H_
#define LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_STATES_STYLE_START_COMMENT_STATE_H_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {

class StyleStartCommentState : public StyleState {
 public:
  void processState(StyleSheetParser &parser) override;
};
}

#endif // LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_STATES_STYLE_START_COMMENT_STATE_H_
