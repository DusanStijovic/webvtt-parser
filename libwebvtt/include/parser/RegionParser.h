#ifndef WEBVTT_REGION_PARSER_H
#define WEBVTT_REGION_PARSER_H

#include "Region.h"
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


        void collectIdSetting(std::u32string_view, std::u32string_view settingValue);

        void collectWidthSetting(std::u32string_view, std::u32string_view settingValue);

        void collectLinesSetting(std::u32string_view, std::u32string_view settingValue);

        void collectAnchorSetting(std::u32string_view, std::u32string_view settingValue);

        void collectViewPortAnchorSetting(std::u32string_view, std::u32string_view settingValue);

        void collectScrollSetting(std::u32string_view, std::u32string_view settingValue);


    };

} //End of namespace

#endif