#ifndef WEBVTT_REGION_PARSER_H
#define WEBVTT_REGION_PARSER_H

#include "elements/Region.h"
#include "ObjectParser.h"
#include <list>
#include <memory>
#include <string>

namespace WebVTT {
    class RegionParser : public ObjectParser<Region> {
    public:

        bool parseSettings(std::u32string_view input);

        virtual ~RegionParser() = default;

    private:

        /**
         * Constexpresions that represent specific region setting
         */
        static constexpr std::u32string_view ID_SETTING = U"id";
        static constexpr std::u32string_view WIDTH_SETTING = U"width";
        static constexpr std::u32string_view LINES_SETTING = U"lines";
        static constexpr std::u32string_view REGION_ANCHOR_SETTING = U"regionanchor";
        static constexpr std::u32string_view VIEW_PORT_ANCHOR_SETTING = U"viewportanchor";
        static constexpr std::u32string_view SCROLL_SETTING = U"scroll";


        /**
         * Parse and set region id
         *
         * @param settingValue value of setting being parsed
         */
        void parseAndSetIdSetting(std::u32string_view settingValue);

        /**
         * Parse and set region width setting
         *
         * @param settingValue value of setting being parsed
         */
        void parseAndSetWidthSetting(std::u32string_view settingValue);


        /**
         *Parse and set region line setting
         *
         * @param settingValue value of setting being parsed
         */
        void parseAndSetLinesSetting(std::u32string_view settingValue);


        /**
         * Parse and set region anchor setting
         *
         * @param settingValue value of setting being parsed
         */
        void parseAndSetAnchorSetting(std::u32string_view settingValue);

        /**
         *Parse and set region view port anchor setting
         *
         * @param settingValue value of setting being parsed
         */
        void parseAndSetViewPortAnchorSetting(std::u32string_view settingValue);

        /**
         * Parse and set region scroll setting
         *
         * @param settingValue value of setting being parsed
         */
        void parseAndSetScrollSetting(std::u32string_view settingValue);


    };

} //End of namespace

#endif