#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_COLLECT_PSEUDO_ARGUMENT_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_COLLECT_PSEUDO_ARGUMENT_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"

namespace webvtt
{
    class StyleCollectPseudoArgument : public StyleState
    {
    public:
        StyleCollectPseudoArgument() = default;
        void processState(StyleSheetParser &parser) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_COLLECT_PSEUDO_CLASS_ARGUMENT_HPP_