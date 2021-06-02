#include "Cue.h"
#include "ParserUtil.h"
#include "utf8.h"

namespace WebVTT
{

    std::optional<long> Cue::colectTimePoint(std::u32string_view input, const char32_t *position)
    {

        TimeUnit timeUnit = TimeUnit::MINUTES;
        uint32_t value1, value2, value3, value4;
        if (position == input.end())
            return std::nullopt;
        if (!ParserUtil::isDigit(*position))
            return std::nullopt;

        std::string collectedTime = ParserUtil::collectDigits(input, position);

        value1 = std::stoi(collectedTime);

        if (collectedTime.length() != 2 || value1 > 59)
        {
            timeUnit = TimeUnit::HOURS;
        }

        if (position == input.end() || *position != COLON)
            return std::nullopt;
        position++;

        collectedTime = ParserUtil::collectDigits(input, position);

        if (collectedTime.length() != 2)
            return std::nullopt;

        value2 = std::stoi(collectedTime);

        if (timeUnit == TimeUnit::HOURS || (position != input.end() && *position == COLON))
        {
            if (position == input.end() || *position != COLON)
                return std::nullopt;
            position++;
            collectedTime = ParserUtil::collectDigits(input, position);
            if (collectedTime.length() != 2)
                return std::nullopt;
            value3 = std::stoi(collectedTime);
        }
        else
        {
            value3 = value2;
            value2 = value1;
            value1 = 0;
        }
        if (position == input.end() || *position != FULL_STOP)
            return std::nullopt;
        position++;

        collectedTime = ParserUtil::collectDigits(input, position);
        if (collectedTime.length() != 3)
            return std::nullopt;

        value4 = std::stoi(collectedTime);

        if (value2 > 59 || value3 > 59)
            return std::nullopt;

        return value1 * 60 * 60 + value2 * 60 + value3 + value4 / 1000;
    }

    std::optional<std::tuple<long, long>> Cue::colectTiming(std::u32string_view input, const char32_t *position)
    {

        ParserUtil::skipWhiteSpaces(input, position);
        if (position == input.end())
            return std::nullopt;

        auto timePoint1 = colectTimePoint(input.substr(position - input.begin()), position);
        if (!timePoint1.has_value())
            return std::nullopt;

        ParserUtil::skipWhiteSpaces(input, position);
        if (position == input.end())
            return std::nullopt;

        if (*position != HYPEN_MINUS)
            return std::nullopt;
        position++;
        if (*position != HYPEN_MINUS)
            return std::nullopt;
        position++;
        if (*position != HYPEN_GREATHER)
            return std::nullopt;
        ParserUtil::skipWhiteSpaces(input, position);

        auto timePoint2 = colectTimePoint(input.substr(position - input.begin()), position);
        if (!timePoint2.has_value())
            return std::nullopt;

        return std::make_tuple(timePoint1.value(), timePoint2.value());
    }

    std::optional<Cue> Cue::collectTextAndSettings(std::u32string_view input, const char32_t *position)
    {
        std::unique_ptr<Cue> cue = std::make_unique<Cue>();
        auto timing = colectTiming(input, position);
        if (!timing.has_value())
            return std::nullopt;
        auto [start, end] = timing.value();
    };

}
