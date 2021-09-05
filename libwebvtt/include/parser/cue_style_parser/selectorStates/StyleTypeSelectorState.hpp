#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES__STYLE_TYPE_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES__STYLE_TYPE_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"

namespace webvtt
{
    class StyleTypeSelectorState : public FetchSelectorState
    {
    public:
        explicit StyleTypeSelectorState() = default;

    private:
        static bool checkIfTypeAllowed(std::u32string_view);
        void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;

        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
        void preprocessBuffer(StyleSheetParser &parser) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES__STYLE_TYPE_SELECTOR_STATE_HPP_
