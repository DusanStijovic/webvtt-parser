#include <Region.h>
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
        if (position == input.end() || *position != COLON_C)
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
        if (timeUnit == TimeUnit::HOURS || (position != input.end() && *position == COLON_C)) {

            // [Collect timestamp] Step 12.a.1
            if (position == input.end() || *position != COLON_C)
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

    void Cue::collectSetting(std::u32string_view input, std::u32string_view::iterator &position) {
        uint32_t currIndex = position - input.begin();
        unsigned long endSettingPos;
        std::u32string settingName, settingValue;

        while ((endSettingPos = input.find_first_of(SPACE_C, currIndex)) != std::u32string_view::npos) {
            auto startSettingPos = currIndex;
            std::u32string_view settingString = input.substr(startSettingPos, endSettingPos);

            currIndex = endSettingPos;
            auto colonPos = settingString.find(COLON_C);
            if (colonPos == std::u32string_view::npos || colonPos == startSettingPos || colonPos == endSettingPos) {
                continue;
            }

            settingName = input.substr(startSettingPos, colonPos);
            settingValue = input.substr(colonPos + 1, endSettingPos);

            if (ParserUtil::compareU32Strings(settingName, CUE_SETTING::REGION)) {
                collectRegionSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, CUE_SETTING::VERTICAL)) {
                collectVerticalSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, CUE_SETTING::LINE)) {
                collectLineSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, CUE_SETTING::POSITION)) {
                collectPositionSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, CUE_SETTING::SIZE)) {
                collectSizeSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, CUE_SETTING::ALIGN)) {
                collectAlignSetting(settingName, settingValue);
                continue;
            }


        }
    }


    bool Cue::collectTimingAndSettings(std::u32string_view input,
                                       std::u32string_view::iterator &position) {
        auto timing = this->collectTiming(input, position);
        if (!timing.has_value())
            return false;
        auto[start, end] = timing.value();
        this->start = start;
        this->end = end;
        this->collectSetting(input, position);
        return true;
    }

    void Cue::collectAlignSetting(std::u32string_view name, std::u32string_view value) {

    }

    void Cue::collectRegionSetting(std::u32string_view name, std::u32string_view value) {

    }

    void Cue::collectVerticalSetting(std::u32string_view name, std::u32string_view value) {

    }

    void Cue::collectLineSetting(std::u32string_view name, std::u32string_view value) {

    }

    void Cue::collectPositionSetting(std::u32string_view name, std::u32string_view value) {

    }

    void Cue::collectSizeSetting(std::u32string_view name, std::u32string_view value) {

    };
}
