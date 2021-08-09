#ifndef STYLE_SHEET_PARSER_H
#define STYLE_SHEET_PARSER_H

#include "parser/ObjectParser.h"
#include "parser/cue_style_parser/states/StyleState.h"

#include "elements/StyleSheet.h"

#include <map>
#include <memory>
#include <string>

namespace WebVTT
{
    class StyleSheetParser : public ObjectParser<StyleSheet>
    {
    public:
        constexpr static std::u32string_view CUE_STYLE_START = U"::cue";
        constexpr static std::u32string_view REGION_STYLE_START = U"region";
        enum class StyleSheetParserState
        {
            START,
            START_SELECTOR,
            CUE_ID_SELECTOR,
            CUE_REGION_ID_SELECTOR,
            CLASS_SELECTOR,
            TYPE_SELECTOR,
            ATTRIBUTE_SELECTOR,
            PSEUDO_CLASS_SELECTOR,
            END_SELECTOR,
            RULES
        };
        void parseCSSRules(std::u32string_view input);
        void setSelectorToCurrentObject(std::shared_ptr<StyleSelector> styleSelector);

        inline std::u32string_view &getInput() { return input; }
        inline typename std::u32string_view::iterator &getCurrentPosition() { return currentPosition; };

        inline void setEndParsing(bool endParsing) { this->endParsing = endParsing; }
        inline bool isEndParsing() { return endParsing; }

        inline std::u32string &getTypeMark() { return type_mark; }

        void setState(StyleSheetParserState newState);

    private:
        bool endParsing = false;
        std::shared_ptr<StyleState> currentState;

        std::u32string_view input;
        typename std::u32string_view::iterator currentPosition;

        std::u32string type_mark;

        void initializeTokenizerStates();

        std::map<StyleSheetParserState, std::shared_ptr<StyleState>> statesInsance;
    };
}

#endif