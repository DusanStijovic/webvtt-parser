#include "CueParser.h"
#include "ParserUtil.h"
#include <iostream>

namespace WebVTT {


    std::optional<long>
    CueParser::collectTimeStamp(std::u32string_view input, std::u32string_view::iterator &position) {

        // [Collect timestamp] Step 2
        Cue::TimeUnit timeUnit = Cue::TimeUnit::MINUTES;
        uint32_t value1, value2, value3, value4;

        // [Collect timestamp] Step 3
        if (position == input.end())
            return std::nullopt;

        // [Collect timestamp] Step 4
        if (!ParserUtil::isDigit(*position))
            return std::nullopt;

        // [Collect timestamp] Step 5
        auto collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
        std::string collectedTime = collectedTimeOptional.value();

        // [Collect timestamp] Step 6
        value1 = std::stoi(collectedTime);

        // [Collect timestamp] Step 7
        if (collectedTime.length() != 2 || value1 > 59) {
            timeUnit = Cue::TimeUnit::HOURS;
        }

        // [Collect timestamp] Step 8
        if (position == input.end() || *position != ParserUtil::COLON_C)
            return std::nullopt;
        position++;

        // [Collect timestamp] Step 9
        collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
        collectedTime = collectedTimeOptional.value();

        // [Collect timestamp] Step 10
        if (collectedTime.length() != 2)
            return std::nullopt;

        // [Collect timestamp] Step 11
        value2 = std::stoi(collectedTime);

        // [Collect timestamp] Step 12
        if (timeUnit == Cue::TimeUnit::HOURS || (position != input.end() && *position == ParserUtil::COLON_C)) {

            // [Collect timestamp] Step 12.a.1
            if (position == input.end() || *position != ParserUtil::COLON_C)
                return std::nullopt;
            position++;

            // [Collect timestamp] Step 12.a.2
            collectedTimeOptional = ParserUtil::collectDigits(input, position);
            if (!collectedTimeOptional.has_value())
                return std::nullopt;
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
        if (position == input.end() || *position != ParserUtil::FULL_STOP)
            return std::nullopt;
        position++;

        // [Collect timestamp] Step 14
        collectedTimeOptional = ParserUtil::collectDigits(input, position);
        if (!collectedTimeOptional.has_value())
            return std::nullopt;
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
    CueParser::collectTiming(std::u32string_view input, std::u32string_view::iterator &position) {
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
        if (*position != ParserUtil::HYPEN_MINUS)
            return std::nullopt;
        position++;
        if (*position != ParserUtil::HYPEN_MINUS)
            return std::nullopt;
        position++;
        if (*position != ParserUtil::HYPEN_GREATHER)
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

    void CueParser::collectSetting(std::u32string_view input, std::u32string_view::iterator &position) {

        std::u32string_view setting;
        std::u32string settingName, settingValue;

        while (!(setting = ParserUtil::parseUntilCharacter(input, ParserUtil::SPACE_C, position)).empty()) {

            auto settingInfoOptional = ParserUtil::splitStringAroundCharacter(setting, ParserUtil::COLON_C);

            if (!settingInfoOptional.has_value()) continue;

            auto[settingName, settingValue] = settingInfoOptional.value();

            if (ParserUtil::compareU32Strings(settingName, Cue::REGION)) {
                collectRegionSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, Cue::VERTICAL)) {
                collectVerticalSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, Cue::LINE)) {
                collectLineSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, Cue::POSITION)) {
                collectPositionSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, Cue::SIZE)) {
                collectSizeSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, Cue::ALIGN)) {
                collectAlignSetting(settingName, settingValue);
                continue;
            }
        }
    }

    bool CueParser::collectTimingAndSettings(std::u32string_view input,
                                             std::u32string_view::iterator &position) {
        if (currentObject == nullptr)
            return false;

        auto timing = this->collectTiming(input, position);
        if (!timing.has_value())
            return false;
        auto[start, end] = timing.value();
        currentObject->setStartTime(start);
        currentObject->setEndTime(end);
        this->collectSetting(input, position);
        return true;
    }

    void CueParser::collectAlignSetting(std::u32string_view name, std::u32string_view value) {
        if (ParserUtil::compareU32Strings(value, U"start")) {
            currentObject->setTextAlignment(Cue::Alignment::START);
            return;
        }
        if (ParserUtil::compareU32Strings(value, U"center")) {
            currentObject->setTextAlignment(Cue::Alignment::CENTER);
            return;
        }
        if (ParserUtil::compareU32Strings(value, U"end")) {
            currentObject->setTextAlignment(Cue::Alignment::END);
            return;
        }
        if (ParserUtil::compareU32Strings(value, U"right")) {
            currentObject->setTextAlignment(Cue::Alignment::RIGHT);
            return;
        }
        if (ParserUtil::compareU32Strings(value, U"left")) {
            currentObject->setTextAlignment(Cue::Alignment::LEFT);
            return;
        }

    }

    void CueParser::collectRegionSetting(std::u32string_view name, std::u32string_view value) {
        
    }

    void CueParser::collectVerticalSetting(std::u32string_view name, std::u32string_view value) {
        Cue::WritingDirection currentWritingDirection = Cue::WritingDirection::HORIZONTAL;
        if (ParserUtil::compareU32Strings(value, U"rl")) {
            currentWritingDirection = Cue::WritingDirection::VERTICAL_GROWING_RIGHT;
        }
        if (ParserUtil::compareU32Strings(value, U"lf")) {
            currentWritingDirection = Cue::WritingDirection::VERTICAL_GROWING_LEFT;
        }
        if (currentWritingDirection != Cue::WritingDirection::HORIZONTAL) {
            currentObject->setRegion(nullptr);
        }
        currentObject->setWritingDirection(currentWritingDirection);
    }

    void CueParser::collectLineSetting(std::u32string_view name, std::u32string_view value) {
        std::u32string_view colPos = value, colAlign;
        auto comaPosition = value.find(U',');
        if (comaPosition != std::u32string_view::npos) {
            colPos = value.substr(0, comaPosition);
            colAlign = value.substr(comaPosition + 1);
        }

        auto position = value.begin() + comaPosition + 1;
        auto percentageStringOptional = ParserUtil::collectPercentage(colAlign, position);
        if (!percentageStringOptional.has_value()) return;
        double number = std::stod(percentageStringOptional.value());


        //Izdvojiti u posebnu funkciju
        if (ParserUtil::compareU32Strings(colAlign, U"line-left")) {
            currentObject->setPositionAlignment(Cue::Alignment::LEFT);
        } else if (ParserUtil::compareU32Strings(colAlign, U"center")) {
            currentObject->setPositionAlignment(Cue::Alignment::CENTER);
        } else if (ParserUtil::compareU32Strings(colAlign, U"line-right")) {
            currentObject->setPositionAlignment(Cue::Alignment::RIGHT);
        } else if (!colAlign.empty()) return;

        currentObject->setPosition(number);


    }

    void CueParser::collectPositionSetting(std::u32string_view name, std::u32string_view value) {
        std::u32string_view linePos = value, lineAlign;
        auto comaPosition = value.find(U',');
        double number = -1;
        if (comaPosition != std::u32string_view::npos) {
            linePos = value.substr(0, comaPosition);
            lineAlign = value.substr(comaPosition + 1);
        }
        auto percentagePos = linePos.find(U'%');
        bool foundPercentageOnLast = (percentagePos == linePos.length() - 1) ? true : false;
        if (percentagePos == std::u32string_view::npos) {
            std::string stringNumber = utf8::utf32to8(linePos);
            number = std::stod(stringNumber);
            //TODO catch error
        } else {
            if (foundPercentageOnLast) {
                std::string stringNumber = utf8::utf32to8(linePos.substr());
                number = std::stoi(stringNumber);
            } else return;
        }

        if (ParserUtil::compareU32Strings(lineAlign, U"start")) {
            currentObject->setLineAlignment(Cue::Alignment::START);
        } else if (ParserUtil::compareU32Strings(lineAlign, U"center")) {
            currentObject->setLineAlignment(Cue::Alignment::CENTER);
        } else if (ParserUtil::compareU32Strings(lineAlign, U"end")) {
            currentObject->setLineAlignment(Cue::Alignment::END);
        } else if (!lineAlign.empty()) return;

        currentObject->setLineNumber(number);


    }

    void CueParser::collectSizeSetting(std::u32string_view name, std::u32string_view value) {
        auto position = value.begin();
        auto percentageStringOptional = ParserUtil::collectPercentage(value, position);
        if (!percentageStringOptional.has_value()) return;

        std::string percentageString = percentageStringOptional.value();
        double percentage = std::stod(percentageString);
        if (percentage < 0 || percentage > 100) return;
        currentObject->setSize(percentage);
        if (percentage != 100) currentObject->setRegion(nullptr);
    };

} // end of namespace