#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_ID_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_ID_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"
namespace webvtt
{

    class StyleIDSelectorState : public FetchSelectorState
    {
    public:
        StyleIDSelectorState() = default;
     

    private:
        virtual void preprocessBuffer(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_IDSELECTORSTATE_HPP_
