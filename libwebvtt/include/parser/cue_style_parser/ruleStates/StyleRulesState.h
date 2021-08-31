#ifndef LIBWEBVTT_STYLERULESSTATE_H
#define LIBWEBVTT_STYLERULESSTATE_H
#include "parser/cue_style_parser/states/StyleState.h"
#include "utf8.h"
#include <string>
#include <set>

namespace WebVTT
{

    class StyleRulesState : public StyleState
    {
    public:
        StyleRulesState() = default;
        virtual void processState(StyleSheetParser &parser) override;

    private:
        void processRule(StyleSheetParser &parser, std::u32string_view input);

    private:
    };
}

#endif //LIBWEBVTT_STYLE_RULES_STATE_H
