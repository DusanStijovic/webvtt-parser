#ifndef LIBWEBVTT_STYLERULESSTATE_H
#define LIBWEBVTT_STYLERULESSTATE_H
#include "parser/cue_style_parser/states/StyleState.h"
#include <string>
#include <set>

namespace WebVTT
{

    class StyleRulesState : public StyleState
    {
    public:
       

        StyleRulesState(StyleSheetParser &styleSheetParser) : StyleState(styleSheetParser)
        {
        }
        virtual void processState() override;

    private:
        virtual void processRule(std::u32string_view name, std::u32string_view value){

        };
        virtual bool isNameAllowed(std::u32string_view name)
        {
            return allowedPropreties.find(name) != allowedPropreties.end();
        };
        virtual void initializeAllowedPropreties() = 0;

    protected:
        std::set<std::u32string_view> allowedPropreties;
    };
}

#endif //LIBWEBVTT_STYLE_RULES_STATE_H
