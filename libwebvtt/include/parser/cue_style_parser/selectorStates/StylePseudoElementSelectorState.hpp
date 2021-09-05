#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_ELEMENT_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_ELEMENT_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"
#include "elements/style_selectors/StyleSelector.hpp"

namespace webvtt
{
    class StylePseudoElementSelectorState : public FetchSelectorState
    {
    public:
        StylePseudoElementSelectorState() = default;

    private:
        void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;
        void preprocessBuffer(StyleSheetParser &parser) override;
        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_ELEMENT_SELECTOR_STATE_HPP_