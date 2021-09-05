#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_CLASS_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_CLASS_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"
namespace webvtt
{

    class StyleClassSelectorState : public FetchSelectorState
    {
    public:
        StyleClassSelectorState() = default;

    private:
        virtual void preprocessBuffer(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_LIB_WEBVTT_CLASS_SELECTOR_STATE_HPP_
