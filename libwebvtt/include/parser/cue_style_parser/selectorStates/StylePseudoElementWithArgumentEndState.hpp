#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_ELEMENT_WITH_ARGUMENT_END_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_ELEMENT_WITH_ARGUMENT_END_STATE_HPP_
#include "parser/cue_style_parser/selectorStates/StylePseudoWithArgumentEndState.hpp"

namespace webvtt
{
    class StylePseudoElementWithArgumentEndState : public StylePseudoWithArgumentEndState
    {
    public:
        StylePseudoElementWithArgumentEndState() = default;
        std::unique_ptr<StyleSelector> makeNewPseudoStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_CLASS_WITH_ARGUMENT_END_STATE_HPP_