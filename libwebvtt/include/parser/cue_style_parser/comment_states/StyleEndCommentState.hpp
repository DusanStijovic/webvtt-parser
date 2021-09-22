#ifndef LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_COMMENT_STATES_STYLE_END_COMMENT_STATE_HPP_
#define LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_COMMENT_STATES_STYLE_END_COMMENT_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt {
class StyleEndCommentState : public StyleState{
 public:
  void processState(StyleSheetParser &parser) override;

};
} // namespace webvtt
#endif // LIBWEBVTT_SOURCE_PARSER_CUE_STYLE_PARSER_COMMENT_STATES_STYLE_END_COMMENT_STATE_HPP_
