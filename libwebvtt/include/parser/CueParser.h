#ifndef WEBVTT_CUE_PARSER_H
#define WEBVTT_CUE_PARSER_H

#include "Cue.h"
#include "ObjectParser.h"
#include <list>
#include <memory>


namespace WebVTT {
    class CueParser : public ObjectParser<Cue> {

    public:
        bool collectTimingAndSettings(std::u32string_view input,
                                      std::u32string_view::iterator &position);

        CueParser(std::list<std::shared_ptr<Region>>&regions) : currentRegions(regions) {
        }


        ~CueParser()

        override =
        default;

    private:

        std::list<std::shared_ptr<Region>> &currentRegions;

        static std::optional<long> collectTimeStamp(std::u32string_view input, std::u32string_view::iterator &position);

        static std::optional<std::tuple<long, long>>
        collectTiming(std::u32string_view input, std::u32string_view::iterator &position);

        void collectSetting(std::u32string_view input, std::u32string_view::iterator &position);

        void collectRegionSetting(std::u32string_view name, std::u32string_view value);

        void collectVerticalSetting(std::u32string_view name, std::u32string_view value);

        void collectLineSetting(std::u32string_view name, std::u32string_view value);

        void collectPositionSetting(std::u32string_view name, std::u32string_view value);

        void collectSizeSetting(std::u32string_view name, std::u32string_view value);

        void collectAlignSetting(std::u32string_view name, std::u32string_view value);


    };

} //End of namespace

#endif
