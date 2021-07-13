#ifndef WEBVTT_CUE_PARSER_H
#define WEBVTT_CUE_PARSER_H

#include "elements/Cue.h"
#include "parser/ObjectParser.h"
#include <list>
#include <memory>

namespace WebVTT
{

    /**
     * Parser used to parse all cue info from string and set related filed.
     *
     * Algorithm and specification used could be found on:
     * https://www.w3.org/TR/webvtt1/#cue-timings-and-settings-parsing
     */
    class CueParser : public ObjectParser<Cue>
    {

    public:
        /**
         * Used to parse timing(start and end time) and setting from input, parsing starts from specified position.
         * Also set fields in current cue object
         * 
         * @param input string being parsed
         * @param position  place in string from which parsing will be started
         * @return true if paring successful and current cue has been set false otherwise
         */
        bool parseTimingAndSettings(std::u32string_view input,
                                    std::u32string_view::iterator &position);

        /**
         * @param regions Reference to the List of regions that has been parsed until now
         */
        explicit CueParser(const std::list<std::shared_ptr<Region>> &regions) : currentRegions(regions) {}

        /**
         *  Needed because super class destructor is pure virtual function
         */
        ~CueParser() override = default;

    private:
        /**
         * Reference to the list of regions that has been parsed until now
         */
        const std::list<std::shared_ptr<Region>> &currentRegions;

    
        static constexpr std::u32string_view TIME_STAMP_SEPARATOR = U"-->";

        /**
         * Constexpresions that represent type of cue setting
         */
        constexpr static std::u32string_view REGION_SETTING = U"region";
        constexpr static std::u32string_view VERTICAL_SETTING = U"vertical";
        constexpr static std::u32string_view LINE_SETTING = U"line";
        constexpr static std::u32string_view POSITION_SETTING = U"position";
        constexpr static std::u32string_view SIZE_SETTING = U"size";
        constexpr static std::u32string_view ALIGN_SETTING = U"align";

        /**
         * Constexpresions for parsing vertical settings
         */
        static constexpr std::u32string_view VERTICAL_LEFT_TO_RIGHT = U"lr";
        static constexpr std::u32string_view VERTICAL_RIGHT_TO_LEFT = U"rl";

        /**
         * Constexpresions for parsing alignment
         */
        static constexpr std::u32string_view START_ALIGNMENT = U"start";
        static constexpr std::u32string_view END_ALIGNMENT = U"end";
        static constexpr std::u32string_view CENTER_ALIGNMENT = U"center";
        static constexpr std::u32string_view RIGHT_ALIGNMENT = U"right";
        static constexpr std::u32string_view LEFT_ALIGNMENT = U"left";

        /**
         * Constexpresions for parsing line settings
         */
        static constexpr std::u32string_view LINE_LEFT = U"line-left";
        static constexpr std::u32string_view LINE_CENTER = U"center";
        static constexpr std::u32string_view LINE_RIGHT = U"line-right";

        /**
         * Parse string(input) starting from specified position and return parsed time in seconds or null if parsing
         * was not finished successfully
         *
         * Time format: hh:mm:ss.ttt
         *
         * @param input string being parser
         * @param place in string from which parsing starts
         * @return time in seconds if parsing was successful, otherwise null
         */
        static std::optional<double>
        parseTimeStamp(std::u32string_view input, std::u32string_view::iterator &position);

        /**
         *Parse string(input) starting from specified position and return tuple of two parsed time in seconds or null if parsing
         * was not finished successfully. Times are separated with specified separator;
         *
         *Time format: hh:mm:ss.ttt separator hh:mm:ss.ttt
         *Any number of spaces around separator are allowed
         *
         * @param input string being parsed
         * @param position place in string from which parsing starts
         * @param time stamp separator
         * @return  tuple with two times in seconds if parsing was successful, otherwise null
         */
        static std::optional<std::tuple<double, double>>
        parseTiming(std::u32string_view input, std::u32string_view::iterator &position,
                    std::u32string_view separator);

        /**
         * Collect settings from input string started from position.
         * This method also sets setting field in current cue.
         * If parsing some setting was not successful function does not have any effects.
         *
         * @param input string being parsed
         * @param position place in string from which parsing starts
         */
        void parseAndSetSetting(std::u32string_view input, std::u32string_view::iterator &position);

        /**
         * Parse and set cue region setting
         *
         * @param value value of setting being parsed
         */
        void parseAndSetRegionSetting(std::u32string_view value);

        /**
         * Parse and set cue vertical setting
         *
         * @param value value of setting being parsed
         */
        void parseAndSetVerticalSetting(std::u32string_view value);

        /**
         * Parse and set cue line setting
         *
         * @param value value of setting being parsed
         */
        void parseAndSetLineSetting(std::u32string_view value);

        /**
         * Parse and set cue position setting
         *
         * @param value value of setting being parsed
         */
        void parseAndSetPositionSetting(std::u32string_view value);

        /**
         * Parse and set cue size setting
         *
         * @param value value of setting being parsed
         */
        void parseAndSetSizeSetting(std::u32string_view value);

        /**
         * Parse and set cue align setting
         *
         * @param value value of setting being parsed
         */
        void parseAndSetAlignSetting(std::u32string_view value);

        /**
         * Parse used style in cue text and make style tree.
         * Style Tree consist od internal(style) and leaf(actual text) nodes
         * 
         * @param defaaultLanguage optional, default cue text language
         */
        void parseTextStyleAndMakeStyleTree(std::u32string_view defaultLanguage = U"");
    };

} //End of namespace

#endif
