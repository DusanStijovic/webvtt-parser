#ifndef LIBWEBVTT_START_STYLE_STATE_H
#define LIBWEBVTT_START_STYLE_STATE_H

#include "parser/cue_style_parser/states/StyleState.h"
#include "elements/webvtt_objects/StyleSheet.h"
#include "string"

namespace WebVTT
{

    class StyleStartState : public StyleState
    {
    public:
        StyleStartState() = default;

        void processState(StyleSheetParser &parser) override;

    private:
        StyleSheet::StyleSheetType decideStyleSheetType(std::u32string_view);

        void decideNextStateWithSelector(StyleSheetParser &parser, StyleSheet::StyleSheetType);

        StyleSheet::StyleSheetType makeAndSetNewStyleSheetForParsing(StyleSheetParser &parser);
    };
}

#endif //LIBWEBVTT_START_STYLE_STATE_H
