#ifndef WEBVTT_PARSER_UTIL_H
#define WEBVTT_PARSER_UTIL_H

#include "utf8.h"
#include <string>
#include <algorithm>
#include <tuple>

namespace WebVTT
{

    class ParserUtil
    {
    public:
        enum SPECIAL_CHARACTER
        {
            NULL_C = 0x0000,
            REPLACEMENT_C = 0xFFFD,
            CR_C = 0x000D,
            LF_C = 0x000A,
            FF_C = 0x000C,
            SPACE_C = 0x0020,
            TAB_C = 0x0009,
            HYPHEN_MINUS = 0x002D,
            HYPHEN_GREATER = 0x003E,
            COLON_C = 0x003A,
            FULL_STOP = 0x002E,
            COMMA_C = 0x002C,
            DOT_C = 0x002E,
            PERCENT_C = 0x0025,
            AMPERSAND_C = 0x0026,
            HYPHEN_LESS = 0x003C,
            EOF_C = 0x0005,
            SOLIDUS_C = 0x002F

        };

        /**
         * Constexpresions for parsing timestamps
         */
        static constexpr int MAX_MINUTES_VALUE = 60;
        static constexpr int MAX_SECONDS_VALUE = 60;
        static constexpr int MAX_MILLISECONDS_VALUE = 1000;

        static constexpr int NUM_OF_DIGITS_FIRST_PART = 2;
        static constexpr int NUM_OF_DIGITS_SECOND_PART = 2;
        static constexpr int NUM_OF_DIGITS_THIRD_PART = 2;
        static constexpr int NUM_OF_DIGITS_FORTH_PART = 3;

        /**
         *Enum representing type of units in cue time stamp while parsing timestamp
         */
        enum class TimeUnit
        {
            HOURS,
            MINUTES,
            SECONDS
        };

        static constexpr std::u32string_view TIME_STAMP_SEPARATOR = U"-->";

        static constexpr std::u32string_view EMPTY_STRING_VIEW = U"";

        static bool isWhiteSpaceCharacter(uint32_t character);

        static bool isDigit(uint32_t character);

        static std::optional<std::string>
        collectDigits(std::u32string_view input, std::u32string_view::iterator &position);

        //TODO add dot option
        static std::optional<double>
        parsePercentage(std::u32string_view input);

        static std::optional<double>
        parseFloatPointingNumber(std::u32string_view input);

        static bool skipWhiteSpaces(std::u32string_view input, std::u32string_view::iterator &position);

        static bool stringEqualStringPlusSpaces(std::u32string_view string, std::u32string_view lookFor);

        static bool stringContainsSeparator(std::u32string_view input, std::u32string_view separator);

        static bool compareU32Strings(std::u32string_view str1, std::u32string_view str2);

        static std::u32string_view
        parseUntilCharacter(std::u32string_view input, uint32_t character, std::u32string_view::iterator &position);

        static std::optional<std::tuple<std::u32string_view, std::u32string_view>>
        splitStringAroundCharacter(std::u32string_view input, uint32_t character);

        static std::optional<std::tuple<double, double>>
        parseCoordinates(std::u32string_view coordinates, uint32_t separator);

        ParserUtil() = delete;

        static void clearAndSetCharacter(std::u32string &input, uint32_t characterToSet)
        {
            input.clear();
            input.push_back(characterToSet);
        }

        static void strip(std::u32string &input, bool (*isAskedCharacter)(uint32_t))
        {
            auto position = input.begin();

            while (isAskedCharacter(*position) && position != input.end())
                position++;
            auto newBegin = position;

            position = input.end();
            while (isAskedCharacter(*position) && position != newBegin)
                position--;

            auto newEnd = position;
            if (newBegin == newEnd)
                input.clear();

            input.erase(input.begin(), newBegin);
            input.erase(newEnd + 1, input.end());
        }

        static void replaceAllSequenceWithOneCharacter(std::u32string input, bool (*isAskedCharacter)(uint32_t))
        {
            auto position = input.begin();
            while (position != input.end())
            {
                while (!isAskedCharacter(*position) && position != input.end())
                    position++;
                if (position == input.end())
                    return;

                auto startPosition = position;
                while (isAskedCharacter(*position) && position != input.end())
                    position++;
                input.erase(startPosition, position);
            }
        }

        static std::optional<double>
        parseTimeStamp(std::u32string_view input, std::u32string_view::iterator &position);
    };

};
#endif