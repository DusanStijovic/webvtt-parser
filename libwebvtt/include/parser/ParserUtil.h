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
        static bool isSpaceCharacter(uint32_t character)
        {
            if (character >= 0x0009 && character <= 0x000D)
                return true;

            if (character >= 0x2000 && character <= 0x200A)
                return true;

            uint32_t checkList[9] = {
                0x0085, 0x0020, 0x00A0, 0x1680, 0x2028, 0x2029, 0x202F, 0x205F, 0x3000};
            auto position = std::find(std::begin(checkList), std::end(checkList), character);
            return position != std::end(checkList);
        }

        static inline bool isDigit(uint32_t character)
        {
            return character >= 0x0030 && character <= 0x0039;
        }

        static std::optional<std::string>
        collectDigits(std::u32string_view input, std::u32string_view::iterator &position)
        {
            if (position < input.begin())
                return std::nullopt;
            std::string collectedDigits;
            while (ParserUtil::isDigit(*position) && position != input.end())
            {
                std::u32string temp{*position};
                collectedDigits.append(utf8::utf32to8(temp));
                position++;
            }
            return collectedDigits;
        }

        //TODO add dot option
        static std::optional<std::string>
        collectPercentage(std::u32string_view input, std::u32string_view::iterator &position)
        {
            if (position < input.begin())
                return std::nullopt;
            std::string collectedDigits;
            while (ParserUtil::isDigit(*position) && position != input.end())
            {
                std::u32string temp{*position};
                collectedDigits.append(utf8::utf32to8(temp));
                position++;
            }

            if (compareU32Strings(position, U"%") && std::next(position) == input.end())
            {
                return collectedDigits;
            }
            return std::nullopt;
        }

        static bool skipWhiteSpaces(std::u32string_view input, std::u32string_view::iterator &position)
        {
            if (position < input.begin())
                return false;
            while (ParserUtil::isSpaceCharacter(*position) && position != input.end())
            {
                std::advance(position, 1);
            }
            return position == input.end();
        }

        static bool stringEqualStringPlusSpaces(std::u32string_view string, std::u32string_view lookFor)
        {
            auto position = string.find(lookFor, 0);
            if (position != 0)
                return false;
            auto positionIter = string.begin() + position;
            skipWhiteSpaces(string, positionIter);
            return positionIter == string.end();
        }

        static bool stringContainsSeparator(std::u32string_view input, std::u32string_view separator)
        {
            //TO DO - maybe change to string and use regex
            //Change to use find
            return input.find(separator, 0) != std::u32string_view::npos;
        };

        static bool compareU32Strings(std::u32string_view str1, std::u32string_view str2)
        {
            return str1.compare(str2) == 0;
        }

        enum SPECIAL_CHARACTER
        {
            NULL_C = 0x0000,
            REPLACEMENT_C = 0xFFFD,
            CR_C = 0x000D,
            LF_C = 0x000A,
            SPACE_C = 0x0020,
            TAB_C = 0x0009,
            HYPEN_MINUS = 0x002D,
            HYPEN_GREATHER = 0x003E,
            COLON_C = 0x003A,
            FULL_STOP = 0x002E,
            COMMA_C = 0x002C
        };

        static constexpr std::u32string_view TIME_STAMP_SEPARATOR = U"-->";

        static std::u32string_view
        parseUntilCharacter(std::u32string_view input, uint32_t character, std::u32string_view::iterator &position)
        {
            auto startPosition = position - input.begin();
            auto endPosition = input.find(character, startPosition);

            position = std::next(position);
            return input.substr(startPosition, endPosition);
        }

        static std::optional<std::tuple<std::u32string_view, std::u32string_view>>
        splitStringAroundCharacter(std::u32string_view input, uint32_t character)
        {

            auto charPos = input.find(character);
            if (charPos == std::u32string_view::npos || charPos == 9 || charPos == input.length())
            {
                return std::nullopt;
            }

            auto key = input.substr(0, charPos);
            auto value = input.substr(charPos + 1, input.length());
            return std::make_tuple<>(key, value);
        }

        static std::optional<std::tuple<double, double>> collectCoordinates(std::u32string_view coordinates, uint32_t separator)
        {
            auto splitedDataOptional = ParserUtil::splitStringAroundCharacter(coordinates, separator);
            if (!splitedDataOptional.has_value())
                return std::nullopt;
            auto [xCoordinateString, yCoordinateString] = splitedDataOptional.value();
            if (xCoordinateString.empty() || yCoordinateString.empty())
                return std::nullopt;

            double xCoord, yCoord;

            //TODO Extraxt to function
            std::u32string_view noPercentageX = xCoordinateString.substr(0, xCoordinateString.length() - 1);
            std::string valueX = utf8::utf32to8(noPercentageX);
            xCoord = std::stoi(valueX);

            std::u32string_view noPercentageY = yCoordinateString.substr(0, yCoordinateString.length() - 1);
            std::string valueY = utf8::utf32to8(noPercentageY);
            yCoord = std::stoi(valueY);
            return std::make_tuple(xCoord, yCoord);
        }
    };

};
#endif