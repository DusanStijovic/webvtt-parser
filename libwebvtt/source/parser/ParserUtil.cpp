#include "parser/ParserUtil.h"
#include "logger/LoggingUtility.h"
#include "exception"
#include <set>

namespace WebVTT
{

    //TODO GIVE NAMES TO CONSTANTS
    bool ParserUtil::isWhiteSpaceCharacter(uint32_t character)
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

    inline bool ParserUtil::isAsciiDecDigit(uint32_t character)
    {
        return character >= 0x0030 && character <= 0x0039;
    }

    inline bool ParserUtil::isAsciiHexDigit(uint32_t character)
    {
        return character >= 0x0030 && character <= 0x0039 ||
               character >= 0x0041 && character <= 0x0046 ||
               character >= 0x0061 && character <= 0x0066;
        //TODO MAybe put constanst instead this digits.
    }

    inline bool ParserUtil::isAsciiAlphaNumeric(uint32_t character)
    {
        if (isAsciiDecDigit(character))
            return true;
        //TODO constants maybe??
        if (character >= 0x0041 && character <= 0x005A || character >= 0x0061 && character <= 0x007A)
            return true;
        return false;
    }

    std::optional<std::string>
    ParserUtil::collectDigits(std::u32string_view input, std::u32string_view::iterator &position)
    {
        return collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
    }

    std::optional<std::string>
    ParserUtil::collectCharacters(std::u32string_view input, std::u32string_view::iterator &position, std::function<bool(uint32_t character)> isLookedCharacter)
    {
        if (position < input.begin())
            return std::nullopt;
        std::string collectedCharacters;
        while (isLookedCharacter(*position) && position != input.end())
        {
            utf8::append(*position, collectedCharacters);
            position++;
        }
        return collectedCharacters;
    }

    //TODO Change implementation to use stoi or collect digits
    std::optional<double>
    ParserUtil::parsePercentage(std::u32string_view input)
    {
        return parseFloatPointingNumber(input.substr(0, input.length()));
    }

    std::optional<double>
    ParserUtil::parseFloatPointingNumber(std::u32string_view input)
    {
        try
        {
            return std::stod(utf8::utf32to8(input));
        }
        catch (const std::out_of_range &e)
        {
            return std::nullopt;
        }
        catch (const std::invalid_argument &e)
        {
            return std::nullopt;
        }
    }

    bool ParserUtil::skipWhiteSpaces(std::u32string_view input, std::u32string_view::iterator &position)
    {
        if (position < input.begin())
            return false;
        while (ParserUtil::isWhiteSpaceCharacter(*position) && position != input.end())
        {
            std::advance(position, 1);
        }
        return position == input.end();
    }

    bool ParserUtil::stringEqualStringPlusSpaces(std::u32string_view string, std::u32string_view lookFor)
    {
        auto position = string.find(lookFor, 0);
        if (position != 0)
            return false;
        auto positionIter = string.begin() + position;
        skipWhiteSpaces(string, positionIter);
        return positionIter == string.end();
    }

    bool ParserUtil::stringContainsSeparator(std::u32string_view input, std::u32string_view separator)
    {
        //TODO - maybe change to string and use regex
        //Change to use find
        return input.find(separator, 0) != std::u32string_view::npos;
    };

    bool ParserUtil::compareU32Strings(std::u32string_view str1, std::u32string_view str2)
    {
        return str1.compare(str2) == 0;
    }

    std::u32string_view
    ParserUtil::parseUntilCharacter(std::u32string_view input, uint32_t character,
                                    std::u32string_view::iterator &position)
    {
        auto startPosition = position - input.begin();
        auto endPosition = input.find(character, startPosition);
        //TODO checks if end reached
        //TODO see where used to check what expexted, iterator to found or next iterator
        position = std::next(position);
        return input.substr(startPosition, endPosition);
    }

    std::u32string_view ParserUtil::parseUntilAnyOfGivenCharacters(std::u32string_view input, std::u32string_view characters, std::u32string_view::iterator &position)
    {
        auto startPosition = position - input.begin();
        auto endPosition = input.find_first_of(characters, startPosition);
        //TODO checks if end reached
        return input.substr(startPosition, endPosition);
    }

    std::optional<std::tuple<std::u32string_view, std::u32string_view>>
    ParserUtil::splitStringAroundCharacter(std::u32string_view input, uint32_t character)
    {

        auto charPos = input.find(character);

        //TODO Check this for all useges
        // if (charPos == std::u32string_view::npos || charPos == 0 || charPos == input.length())
        // {
        //     return std::nullopt;
        // }

        if (charPos == std::u32string_view::npos)
        {
            return std::nullopt;
        }
        if (charPos == 0)
            return std::make_tuple<>(std::u32string_view(), input);

        if (charPos == input.length() - 1)
            return std::make_tuple<>(input, std::u32string_view());

        auto key = input.substr(0, charPos);
        auto value = input.substr(charPos + 1, input.length());
        return std::make_tuple<>(key, value);
    }

    std::optional<std::tuple<double, double>>
    ParserUtil::parseCoordinates(std::u32string_view coordinates, uint32_t separator)
    {
        auto splitDataOptional = ParserUtil::splitStringAroundCharacter(coordinates, separator);
        if (!splitDataOptional.has_value())
            return std::nullopt;
        auto [xCoordinateString, yCoordinateString] = splitDataOptional.value();
        if (xCoordinateString.empty() || yCoordinateString.empty())
            return std::nullopt;

        double xCoord, yCoord;

        auto xCordOptional = ParserUtil::parsePercentage(xCoordinateString);
        if (!xCordOptional.has_value())
            return std::nullopt;

        auto yCoordOptional = ParserUtil::parsePercentage(yCoordinateString);
        if (!yCoordOptional.has_value())
            return std::nullopt;

        return std::make_tuple(xCordOptional.value(), yCoordOptional.value());
    }

    std::optional<double>
    ParserUtil::parseTimeStamp(std::u32string_view input, std::u32string_view::iterator &position)
    {

        TimeUnit timeUnit = TimeUnit::MINUTES;
        uint32_t value1, value2, value3, value4;

        if (position == input.end())
            return std::nullopt;

        if (!ParserUtil::isAsciiDecDigit(*position))
            return std::nullopt;

        auto collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
        std::string collectedTime = collectedTimeOptional.value();

        value1 = std::stoi(collectedTime);

        if (collectedTime.length() != NUM_OF_DIGITS_FIRST_PART || value1 >= MAX_MINUTES_VALUE)
        {
            timeUnit = TimeUnit::HOURS;
        }

        if (position == input.end() || *position != ParserUtil::COLON_C)
            return std::nullopt;
        position++;

        collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
        collectedTime = collectedTimeOptional.value();

        if (collectedTime.length() != NUM_OF_DIGITS_SECOND_PART)
            return std::nullopt;

        value2 = std::stoi(collectedTime);

        //Check if first parsed digit is hours or minutes
        if (timeUnit == TimeUnit::HOURS || (position != input.end() && *position == ParserUtil::COLON_C))
        {

            if (position == input.end() || *position != ParserUtil::COLON_C)
                return std::nullopt;
            position++;

            collectedTimeOptional = ParserUtil::collectDigits(input, position);
            if (!collectedTimeOptional.has_value())
                return std::nullopt;
            collectedTime = collectedTimeOptional.value();

            if (collectedTime.length() != NUM_OF_DIGITS_THIRD_PART)
                return std::nullopt;

            value3 = std::stoi(collectedTime);
        }
        else
        {
            //TODO Check if need some condition here
            value3 = value2;
            value2 = value1;
            value1 = 0;
        }

        if (position == input.end() || *position != ParserUtil::FULL_STOP)
            return std::nullopt;
        position++;

        collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
        collectedTime = collectedTimeOptional.value();

        if (collectedTime.length() != NUM_OF_DIGITS_FORTH_PART)
            return std::nullopt;

        value4 = std::stoi(collectedTime);

        if (value2 >= MAX_MINUTES_VALUE || value3 >= MAX_SECONDS_VALUE)
            return std::nullopt;

        return value1 * MAX_MINUTES_VALUE * MAX_SECONDS_VALUE + value2 * MAX_SECONDS_VALUE + value3 +
               ((double)value4) / MAX_MILLISECONDS_VALUE;
    }

    std::u32string ParserUtil::parseHTMLNumberReference(std::u32string_view input, std::u32string_view::iterator &currentPosition)
    {
        auto position = currentPosition;

        uint8_t base;
        std::optional<std::string> result;

        position++;
        if (position == input.end())
        {
            return U"";
        }

        if (*position == ParserUtil::LATIN_CAPITAL_LETTER_X || *position == ParserUtil::LATIN_SMALL_LETTER_X)
        {
            position++; //Skip X or x
            result = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiHexDigit);
            base = 16;
        }
        else
        {
            result = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
            base = 10;
        }
        if (position != input.end() || *position == ParserUtil::SEMI_COLON)
        {
            position++;
        }
        else
        {
            //TODO logerror
        }
        if (!result.has_value())
        {
            return U"";
        }
        //Check if number reference is allowd
        uint32_t number = std::stoi(result.value(), nullptr, base);

        currentPosition = position;

        auto iter = numberHTMLReferences.find(number);
        if (iter != numberHTMLReferences.end())
        {
            //TODO log error
            return iter->second;
        }
        if (number >= 0xD800 && number <= 0xDFFF || number > 0x10FFFF)
        {
            //TODO log error
            //TODO maybe put some constants name here
            return {ParserUtil::REPLACEMENT_C};
        }

        for (int i = 0; i < std::size(low_border); i++)
        {
            if (number >= low_border[i] && number <= high_border[i])
            {
                //TODO log error;
            }
        }

        if (unallowedNumbers.find(number) != unallowedNumbers.end())
        {
            //TODO log error;
        }
        return {number};
    }
    std::u32string ParserUtil::parseHTMLNamedReference(std::u32string_view input, std::u32string_view::iterator &currentPosition, bool isInAttribute)
    {
        auto position = currentPosition;

        if (position == input.end())
            return U"";

        std::string forMatching;
        std::map<std::string, std::u32string>::const_iterator found;

        int range = 1;

        while (range <= ParserUtil::MAX_NAMED_HTML_REF_LENGTH &&
               position != input.end() &&
               *position != ParserUtil::SEMI_COLON)
        {
            utf8::append(*position, forMatching);

            auto iter = namedHTMLREferences.find(forMatching);
            if (iter != namedHTMLREferences.end())
                found = iter;
            position++;
            range++;
        }
        if (*position == ParserUtil::SEMI_COLON)
        {
            utf8::append(*position, forMatching);
            auto iter = namedHTMLREferences.find(forMatching);
            if (iter != namedHTMLREferences.end())
                found = iter;
        }

        if (found == namedHTMLREferences.end())
        {
            bool potentialError = true;
            std::string_view check = forMatching;
            for (char one : check.substr(0, forMatching.length() - 1))
            {
                if (!ParserUtil::isAsciiAlphaNumeric(one))
                    potentialError = false;
            }
            if (check.back() != ParserUtil::SEMI_COLON)
            {
                potentialError = false;
            }
            if (potentialError)
            {
                //TODO log error
            }
            //TODO Check if only alphanumeruc ascii is in forMatching

            return U"";
        }

        if (isInAttribute && forMatching.back() != ';' && position != input.end())
        {
            if (*position == '=' || ParserUtil::isAsciiAlphaNumeric(*position))
            {
                return U"";
            }
        }

        if (position != input.end() && *position == '=')
        {
            //TODO Log error
        }

        if (forMatching.back() != ';')
        {
            //TODO log error;
        }
        currentPosition = position;
        return found->second;
        //TODO ADD check for = mark
    }

    std::u32string ParserUtil::consumeHTMLCharacter(std::u32string_view input, std::u32string_view::iterator &currentPosition,
                                                    std::optional<uint32_t> additionalCharacter, bool isInAttribute)
    {

        if (currentPosition == input.end())
            return U"";

        if (additionalCharacter.has_value() && additionalCharacter.value() == *currentPosition)
            return U"";

        std::u32string result;

        switch (*currentPosition)
        {
        case ParserUtil::TAB_C:
        case ParserUtil::LF_C:
        case ParserUtil::FF_C:
        case ParserUtil::SPACE_C:
        case ParserUtil::HYPHEN_LESS:
        case ParserUtil::AMPERSAND_C:
            result = U"";
            break;
        case ParserUtil::HASHTAG_C:
            result = ParserUtil::parseHTMLNumberReference(input, currentPosition);
            break;
        default:
            result = ParserUtil::parseHTMLNamedReference(input, currentPosition, isInAttribute);
            break;
        }
        return result;
    }

    std::u32string ParserUtil::convertCSSEscapedString(std::u32string_view input)
    {
        auto position = input.begin();
        std::u32string convertedString;

        while (position != input.end())
        {
            convertedString.append(ParserUtil::parseUntilCharacter(input, ParserUtil::BACK_SLASH_C, position));
            if (position == input.end())
                break;
            position++;

            std::u32string_view parsedString = ParserUtil::parseUntilAndWhileAskedCharacter(
                input, position,
                ParserUtil::isAsciiHexDigit,
                ParserUtil::isWhiteSpaceCharacter,
                ParserUtil::MAX_NUMBER_OF_CSS_ESCAPED_CHARACTER);

            if (parsedString.empty())
                break;

            uint32_t number = std::stoi(utf8::utf32to8(parsedString), nullptr, 16);
            convertedString.push_back(number);
            //TODO catch exception maybe
        }
        return convertedString;
    }

    std::u32string_view
    ParserUtil::parseUntilAndWhileAskedCharacter(std::u32string_view input, std::u32string_view::iterator &position,
                                                 std::function<bool(uint32_t)> whileCharacter, std::function<bool(uint32_t)> untilCharacter,
                                                 uint32_t maxNumberOfCharacters)
    {
        int startPosition = position - input.begin();
        int length;
        int iteration = 0;
        while (position != input.end() && !untilCharacter(*position) && whileCharacter(*position) &&
               iteration < maxNumberOfCharacters)
        {
            length++;
            iteration++;
            position++;
        }
        return input.substr(startPosition, length);
    }
};
