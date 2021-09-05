#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_END_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_END_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt
{

    class StyleEndSelectorState : public StyleState
    {
    public:
        StyleEndSelectorState() = default;
        void processState(StyleSheetParser &parser) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_ENDSELECTORSTATE_HPP_
