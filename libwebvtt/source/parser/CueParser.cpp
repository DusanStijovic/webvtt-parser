#include "parser/CueParser.h"
#include "parser/ParserUtil.h"
#include <iostream>

namespace WebVTT {

    bool CueParser::parseTimingAndSettings(std::u32string_view input,
                                           std::u32string_view::iterator &position) {
        if (currentObject == nullptr)
            return false;

        auto timing = this->parseTiming(input, position, TIME_STAMP_SEPARATOR);
        if (!timing.has_value())
            return false;

        auto[start, end] = timing.value();
        currentObject->setStartTime(start);
        currentObject->setEndTime(end);

        this->parseAndSetSetting(input, position);
        return true;
    }

    std::optional<double>
    CueParser::parseTimeStamp(std::u32string_view input, std::u32string_view::iterator &position) {

        Cue::TimeUnit timeUnit = Cue::TimeUnit::MINUTES;
        uint32_t value1, value2, value3, value4;

        if (position == input.end())
            return std::nullopt;

        if (!ParserUtil::isDigit(*position))
            return std::nullopt;

        auto collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
        std::string collectedTime = collectedTimeOptional.value();

        value1 = std::stoi(collectedTime);

        if (collectedTime.length() != NUM_OF_DIGITS_FIRST_PART || value1 >= MAX_MINUTES_VALUE) {
            timeUnit = Cue::TimeUnit::HOURS;
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
        if (timeUnit == Cue::TimeUnit::HOURS || (position != input.end() && *position == ParserUtil::COLON_C)) {

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
        } else {
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
               ((double) value4) / MAX_MILLISECONDS_VALUE;
    }

    std::optional<std::tuple<double, double>>
    CueParser::parseTiming(std::u32string_view input, std::u32string_view::iterator &position,
                           std::u32string_view separator) {

        ParserUtil::skipWhiteSpaces(input, position);
        if (position == input.end())
            return std::nullopt;

        auto timePoint1 = parseTimeStamp(input.substr(position - input.begin()), position);
        if (!timePoint1.has_value())
            return std::nullopt;

        ParserUtil::skipWhiteSpaces(input, position);
        if (position == input.end())
            return std::nullopt;

        std::u32string_view temp = input.substr(position - input.begin(), separator.length());
        if (!ParserUtil::compareU32Strings(separator, temp))
            return std::nullopt;

        position = position + separator.length();

        ParserUtil::skipWhiteSpaces(input, position);

        auto timePoint2 = parseTimeStamp(input.substr(position - input.begin()), position);
        if (!timePoint2.has_value())
            return std::nullopt;

        return std::make_tuple(timePoint1.value(), timePoint2.value());
    }

    void CueParser::parseAndSetSetting(std::u32string_view input, std::u32string_view::iterator &position) {

        std::u32string_view setting;
        std::u32string settingName, settingValue;

        while (!(setting = ParserUtil::parseUntilCharacter(input, ParserUtil::SPACE_C, position)).empty()) {

            auto settingInfoOptional = ParserUtil::splitStringAroundCharacter(setting, ParserUtil::COLON_C);

            if (!settingInfoOptional.has_value())
                continue;

            auto[settingName, settingValue] = settingInfoOptional.value();

            if (ParserUtil::compareU32Strings(settingName, REGION_SETTING)) {
                parseAndSetRegionSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, VERTICAL_SETTING)) {
                parseAndSetVerticalSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, LINE_SETTING)) {
                parseAndSetPositionSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, POSITION_SETTING)) {
                parseAndSetPositionSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, SIZE_SETTING)) {
                parseAndSetSizeSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, ALIGN_SETTING)) {
                parseAndSetAlignSetting(settingValue);
                continue;
            }
        }
    }

    void CueParser::parseAndSetAlignSetting(std::u32string_view value) {
        if (ParserUtil::compareU32Strings(value, START_ALIGNMENT)) {
            currentObject->setTextAlignment(Cue::Alignment::START);
            return;
        }
        if (ParserUtil::compareU32Strings(value, CENTER_ALIGNMENT)) {
            currentObject->setTextAlignment(Cue::Alignment::CENTER);
            return;
        }
        if (ParserUtil::compareU32Strings(value, END_ALIGNMENT)) {
            currentObject->setTextAlignment(Cue::Alignment::END);
            return;
        }
        if (ParserUtil::compareU32Strings(value, RIGHT_ALIGNMENT)) {
            currentObject->setTextAlignment(Cue::Alignment::RIGHT);
            return;
        }
        if (ParserUtil::compareU32Strings(value, LEFT_ALIGNMENT)) {
            currentObject->setTextAlignment(Cue::Alignment::LEFT);
            return;
        }
    }

    void CueParser::parseAndSetRegionSetting(std::u32string_view value) {

        std::shared_ptr<Region> foundRegion = Region::getRegionByIdentifier(currentRegions, value);
        if (foundRegion == nullptr)
            return;
        currentObject->setRegion(foundRegion);
    }

    void CueParser::parseAndSetVerticalSetting(std::u32string_view value) {

        Cue::WritingDirection currentWritingDirection = Cue::WritingDirection::HORIZONTAL;
        if (ParserUtil::compareU32Strings(value, VERTICAL_RIGHT_TO_LEFT)) {
            currentWritingDirection = Cue::WritingDirection::VERTICAL_GROWING_RIGHT;
        }

        if (ParserUtil::compareU32Strings(value, VERTICAL_LEFT_TO_RIGHT)) {
            currentWritingDirection = Cue::WritingDirection::VERTICAL_GROWING_LEFT;
        }

        currentObject->setWritingDirection(currentWritingDirection);
    }

    void CueParser::parseAndSetPositionSetting(std::u32string_view value) {
        std::u32string_view colPos = value, colAlign;

        auto splitStrings = ParserUtil::splitStringAroundCharacter(value, ParserUtil::COMMA_C);
        if (splitStrings.has_value()) {
            auto[colPosHelp, colAlignHelp] = splitStrings.value();
            colPos = std::move(colPosHelp);
            colAlign = std::move(colAlignHelp);
        }

        auto percentageOptional = ParserUtil::parsePercentage(colPos);
        if (!percentageOptional.has_value())
            return;
        double number = percentageOptional.value();

        if (ParserUtil::compareU32Strings(colAlign, LINE_LEFT)) {
            currentObject->setPositionAlignment(Cue::Alignment::LEFT);
        } else if (ParserUtil::compareU32Strings(colAlign, LINE_CENTER)) {
            currentObject->setPositionAlignment(Cue::Alignment::CENTER);
        } else if (ParserUtil::compareU32Strings(colAlign, LINE_RIGHT)) {
            currentObject->setPositionAlignment(Cue::Alignment::RIGHT);
        } else if (!colAlign.empty())
            return;

        currentObject->setPosition(number);
    }

    void CueParser::parseAndSetLineSetting(std::u32string_view value) {
        std::u32string_view linePos = value, lineAlign;
        std::optional<double> optionalNumber;
        double number;

        auto splitStrings = ParserUtil::splitStringAroundCharacter(value, ParserUtil::COMMA_C);
        if (splitStrings.has_value()) {
            auto[linePosHelp, lineAlignHelp] = splitStrings.value();
            linePos = std::move(linePosHelp);
            lineAlign = std::move(lineAlignHelp);
        }
        auto percentagePos = linePos.find(ParserUtil::PERCENT_C);
        bool percentageOnLastPosition = (percentagePos == linePos.length() - 1);
        bool percentageFound = (percentagePos == std::u32string_view::npos);

        if (percentageFound && !percentageOnLastPosition)
            return;

        if (percentageOnLastPosition) {
            optionalNumber = ParserUtil::parsePercentage(linePos);
        } else {
            optionalNumber = ParserUtil::parseFloatPointingNumber(linePos);
        }

        if (!optionalNumber.has_value())
            return;
        number = optionalNumber.value();

        if (ParserUtil::compareU32Strings(lineAlign, START_ALIGNMENT)) {
            currentObject->setLineAlignment(Cue::Alignment::START);
        } else if (ParserUtil::compareU32Strings(lineAlign, CENTER_ALIGNMENT)) {
            currentObject->setLineAlignment(Cue::Alignment::CENTER);
        } else if (ParserUtil::compareU32Strings(lineAlign, END_ALIGNMENT)) {
            currentObject->setLineAlignment(Cue::Alignment::END);
        } else if (!lineAlign.empty())
            return;

        currentObject->setLineNumber(number);

        bool newSnapToLines = true;
        if (percentageOnLastPosition) {
            newSnapToLines = false;
        }
        currentObject->setSnapToLines(newSnapToLines);

    }

    void CueParser::parseAndSetSizeSetting(std::u32string_view value) {
        auto position = value.begin();
        auto percentageStringOptional = ParserUtil::parsePercentage(value);
        if (!percentageStringOptional.has_value())
            return;

        double percentage = percentageStringOptional.value();
        if (percentage < 0 || percentage > 100)
            return;
        currentObject->setSize(percentage);
    }

    void CueParser::parseTextStyleAndMakeStyleTree() {


    };

} // end of namespace