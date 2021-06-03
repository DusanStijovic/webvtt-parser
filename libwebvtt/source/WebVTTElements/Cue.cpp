#include "Cue.h"
#include "ParserUtil.h"
#include "utf8.h"

namespace WebVTT {

    std::optional<long> Cue::collectTimeStamp(std::u32string_view input, std::u32string_view::iterator &position) {

        // [Collect timestamp] Step 2
        TimeUnit timeUnit = TimeUnit::MINUTES;
        uint32_t value1, value2, value3, value4;

        // [Collect timestamp] Step 3
        if (position == input.end())
            return std::nullopt;

        // [Collect timestamp] Step 4
        if (!ParserUtil::isDigit(*position))
            return std::nullopt;

        // [Collect timestamp] Step 5
        auto collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value()) return std::nullopt;
        std::string collectedTime = collectedTimeOptional.value();

        // [Collect timestamp] Step 6
        value1 = std::stoi(collectedTime);

        // [Collect timestamp] Step 7
        if (collectedTime.length() != 2 || value1 > 59) {
            timeUnit = TimeUnit::HOURS;
        }

        // [Collect timestamp] Step 8
        if (position == input.end() || *position != COLON)
            return std::nullopt;
        position++;

        // [Collect timestamp] Step 9
        collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value()) return std::nullopt;
        collectedTime = collectedTimeOptional.value();

        // [Collect timestamp] Step 10
        if (collectedTime.length() != 2)
            return std::nullopt;

        // [Collect timestamp] Step 11
        value2 = std::stoi(collectedTime);

        // [Collect timestamp] Step 12
        if (timeUnit == TimeUnit::HOURS || (position != input.end() && *position == COLON)) {

            // [Collect timestamp] Step 12.a.1
            if (position == input.end() || *position != COLON)
                return std::nullopt;
            position++;

            // [Collect timestamp] Step 12.a.2
            collectedTimeOptional = ParserUtil::collectDigits(input, position);
            if (!collectedTimeOptional.has_value()) return std::nullopt;
            collectedTime = collectedTimeOptional.value();

            // [Collect timestamp] Step 12.a.3
            if (collectedTime.length() != 2)
                return std::nullopt;

            // [Collect timestamp] Step 12.a.4
            value3 = std::stoi(collectedTime);
        } else {
            // [Collect timestamp] Step 12.b.1
            //TO DO Check if need some condition here
            value3 = value2;
            value2 = value1;
            value1 = 0;
        }
        // [Collect timestamp] Step 13
        if (position == input.end() || *position != FULL_STOP)
            return std::nullopt;
        position++;

        // [Collect timestamp] Step 14
        collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value()) return std::nullopt;
        collectedTime = collectedTimeOptional.value();

        // [Collect timestamp] Step 15
        if (collectedTime.length() != 3)
            return std::nullopt;

        // [Collect timestamp] Step 16
        value4 = std::stoi(collectedTime);

        // [Collect timestamp] Step 17
        if (value2 > 59 || value3 > 59)
            return std::nullopt;

        // [Collect timestamp] Step [18-19]
        return value1 * 60 * 60 + value2 * 60 + value3 + value4 / 1000;
    }

    std::optional<std::tuple<long, long>>
    Cue::collectTiming(std::u32string_view input, std::u32string_view::iterator &position) {
        // [Collect cue timing] Step 3
        ParserUtil::skipWhiteSpaces(input, position);
        if (position == input.end())
            return std::nullopt;


        // [Collect cue timing] Step 4
        auto timePoint1 = collectTimeStamp(input.substr(position - input.begin()), position);
        if (!timePoint1.has_value())
            return std::nullopt;

        // [Collect cue timing] Step 5
        ParserUtil::skipWhiteSpaces(input, position);
        if (position == input.end())
            return std::nullopt;

        // [Collect cue timing] Steps [6-8]
        if (*position != HYPEN_MINUS)
            return std::nullopt;
        position++;
        if (*position != HYPEN_MINUS)
            return std::nullopt;
        position++;
        if (*position != HYPEN_GREATHER)
            return std::nullopt;
        position++;

        // [Collect cue timing] Step 9
        ParserUtil::skipWhiteSpaces(input, position);

        // [Collect cue timing] Step 10
        auto timePoint2 = collectTimeStamp(input.substr(position - input.begin()), position);
        if (!timePoint2.has_value())
            return std::nullopt;

        return std::make_tuple(timePoint1.value(), timePoint2.value());
    }



    bool Cue::collectTimingAndSettings(std::unique_ptr<Cue> &cue, std::u32string_view input, std::u32string_view::iterator &position) {
        auto timing = collectTiming(input, position);
        if (!timing.has_value())
            return false;
        auto[start, end] = timing.value();
        return true;
    };
}
