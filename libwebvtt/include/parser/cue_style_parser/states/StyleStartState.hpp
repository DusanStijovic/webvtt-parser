#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES__START_STYLE_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES__START_STYLE_STATE_HPP_

#include "parser/cue_style_parser/states/StyleState.hpp"
#include "elements/webvtt_objects/StyleSheet.hpp"
#include "string"

namespace webvtt
{

    class StyleStartState : public StyleState
    {
    public:
        StyleStartState() = default;

        void processState(StyleSheetParser &parser) override;

    private:
        StyleSheet::StyleSheetType decideStyleSheetType(std::u32string_view);

        StyleSheet::StyleSheetType makeAndSetNewStyleSheetForParsing(StyleSheetParser &parser);
    };
}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES__START_STYLE_STATE_HPP_
