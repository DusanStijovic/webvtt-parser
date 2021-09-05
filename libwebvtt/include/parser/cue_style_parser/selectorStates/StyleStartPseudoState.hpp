#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_START_PSEUDO_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_START_PSEUDO_STATE_HPP_

#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt
{

    class StyleStartPseudoState : public StyleState
    {
    public:
        StyleStartPseudoState() = default;
        void processState(StyleSheetParser &parser) override;

    private:
    };
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_START_PSEUDO_STATE_HPP_