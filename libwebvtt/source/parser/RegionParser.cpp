#include "parser/RegionParser.h"
#include "parser/ParserUtil.h"

namespace WebVTT {

    bool RegionParser::parseSettings(std::u32string_view input) {
        std::u32string_view setting;
        std::u32string settingName, settingValue;
        auto position = input.begin();

        while (!(setting = ParserUtil::parseUntilCharacter(input, ParserUtil::SPACE_C, position)).empty()) {
            auto settingInfoOptional = ParserUtil::splitStringAroundCharacter(setting, ParserUtil::COLON_C);

            if (!settingInfoOptional.has_value())
                continue;

            auto[settingName, settingValue] = settingInfoOptional.value();
            if (ParserUtil::compareU32Strings(settingName, ID_SETTING)) {
                parseAndSetIdSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, WIDTH_SETTING)) {
                parseAndSetWidthSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, LINES_SETTING)) {
                parseAndSetLinesSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, REGION_ANCHOR_SETTING)) {
                parseAndSetAnchorSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, VIEW_PORT_ANCHOR_SETTING)) {
                parseAndSetViewPortAnchorSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, SCROLL_SETTING)) {
                parseAndSetScrollSetting(settingValue);
                continue;
            }
        }
        return true;
    }

    void RegionParser::parseAndSetIdSetting(std::u32string_view settingValue) {
        currentObject->setId(settingValue);
    }

    void RegionParser::parseAndSetWidthSetting(std::u32string_view settingValue) {
        std::u32string_view value_view = settingValue.substr(0, settingValue.length() - 1);

        std::string value = utf8::utf32to8(value_view);

        currentObject->setWidth(std::stod(value));
    }

    void RegionParser::parseAndSetLinesSetting(std::u32string_view settingValue) {
        std::string value = utf8::utf32to8(settingValue);

        currentObject->setLines(std::stoi(value));
    }

    void RegionParser::parseAndSetAnchorSetting(std::u32string_view settingValue) {
        auto optionalCoordinates = ParserUtil::parseCoordinates(settingValue, ParserUtil::COMMA_C);
        if (!optionalCoordinates.has_value())
            return;

        auto[xCoord, yCoord] = optionalCoordinates.value();

        currentObject->setAnchor({xCoord, yCoord});
    }

    void RegionParser::parseAndSetViewPortAnchorSetting(std::u32string_view settingValue) {
        auto optionalCoordinates = ParserUtil::parseCoordinates(settingValue, ParserUtil::COMMA_C);
        if (!optionalCoordinates.has_value())
            return;

        auto[xCoord, yCoord] = optionalCoordinates.value();

        currentObject->setViewAnchorPort({xCoord, yCoord});
    }

    void RegionParser::parseAndSetScrollSetting(std::u32string_view settingValue) {
        if (ParserUtil::compareU32Strings(settingValue, U"up")) {
            currentObject->setScrollValue(Region::ScrollType::UP);
        }
    }
}