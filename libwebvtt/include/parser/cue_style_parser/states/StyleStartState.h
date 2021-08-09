#ifndef LIBWEBVTT_START_STYLE_STATE_H
#define LIBWEBVTT_START_STYLE_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"
#include "string"

namespace WebVTT
{

    class StyleStartState : public StyleState
    {
    public:
        StyleStartState(StyleSheetParser &styleSheetParser) : StyleState(styleSheetParser) {}
        virtual void processState() override;

    private:
        bool checkIfInputStartWith(std::u32string_view string);
    };
}

#endif //LIBWEBVTT_START_STYLE_STATE_H
