#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_WITH_ARGUMENT_END_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_WITH_ARGUMENT_END_STATE_HPP_

#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"

namespace webvtt
{
    class StylePseudoWithArgumentEndState : public FetchSelectorState
    {
    public:
        StylePseudoWithArgumentEndState() = default;
        void preprocessBuffer(StyleSheetParser &parser) override;
        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewPseudoStyleSelector(StyleSheetParser &parser) = 0;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_WITH_ARGUMENT_END_STATE_HPP_