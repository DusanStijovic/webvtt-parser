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
            SPACE_C = 0x0020,
            TAB_C = 0x0009,
            HYPHEN_MINUS = 0x002D,
            HYPHEN_GREATER = 0x003E,
            COLON_C = 0x003A,
            FULL_STOP = 0x002E,
            COMMA_C = 0x002C,
            DOT_C = 0x002E,
            PERCENT_C = 0x0025
        };

        static constexpr std::u32string_view TIME_STAMP_SEPARATOR = U"-->";

        static bool isSpaceCharacter(uint32_t character);

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
    };

};
#endif