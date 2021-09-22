#ifndef LIBWEBVTT_SOURCE_PARSER_STYLE_OMMENT_STATES_COMMENT_STATE_HPP_
#define LIBWEBVTT_SOURCE_PARSER_STYLE_OMMENT_STATES_COMMENT_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {
class StyleCommentState : public StyleState {
 public:
  void processState(StyleSheetParser &parser) override;

};

} // namespace webvtt

#endif // LIBWEBVTT_SOURCE_PARSER_STYLE_OMMENT_STATES_COMMENT_STATE_HPP_
