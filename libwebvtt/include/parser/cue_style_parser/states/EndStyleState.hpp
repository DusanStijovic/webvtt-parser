#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES_END_STYLE_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES_END_STYLE_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt
{
    class EndStyleState : public StyleState
    {
    public:
        EndStyleState() = default;
        virtual void processState(StyleSheetParser &parser) override;
    };
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES_END_STYLE_STATE_HPP_