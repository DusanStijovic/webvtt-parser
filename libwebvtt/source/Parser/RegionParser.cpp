#include "RegionParser.h"
#include "ParserUtil.h"

namespace WebVTT
{

    bool RegionParser::parseSettings(std::u32string_view input)
    {
        std::u32string_view setting;
        std::u32string settingName, settingValue;
        auto position = input.begin();

        while (!(setting = ParserUtil::parseUntilCharacter(input, ParserUtil::SPACE_C, position)).empty())
        {
            auto settingInfoOptional = ParserUtil::splitStringAroundCharacter(setting, ParserUtil::COLON_C);

            if (!settingInfoOptional.has_value())
                continue;

            auto [settingName, settingValue] = settingInfoOptional.value();
            if (ParserUtil::compareU32Strings(settingName, U"id"))
            {
                collectIdSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, U"width"))
            {
                collectWidthSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, U"lines"))
            {
                collectLinesSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, U"regionanchor"))
            {
                collectAnchorSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, U"viewportanchor"))
            {
                collectViewPortAnchorSetting(settingName, settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, U"scroll"))
            {
                collectScrollSetting(settingName, settingValue);
                continue;
            }
        }
    }

    void RegionParser::collectIdSetting(std::u32string_view, std::u32string_view settingValue)
    {
        currentObject->setId(settingValue);
    }

    void WebVTT::RegionParser::collectWidthSetting(std::u32string_view, std::u32string_view settingValue)
    {
        std::u32string_view value_view = settingValue.substr(0, settingValue.length() - 1);

        std::string value = utf8::utf32to8(value_view);

        currentObject->setWidth(std::stod(value));
    }

    void RegionParser::collectLinesSetting(std::u32string_view, std::u32string_view settingValue)
    {
        std::string value = utf8::utf32to8(settingValue);

        currentObject->setLines(std::stoi(value));
    }

    void RegionParser::collectAnchorSetting(std::u32string_view, std::u32string_view settingValue)
    {
        auto optionalCoordinates = ParserUtil::collectCoordinates(settingValue, ParserUtil::COMMA_C);
        if (!optionalCoordinates.has_value())
            return;

        auto [xCoord, yCoord] = optionalCoordinates.value();

        currentObject->setAnchor({xCoord, yCoord});
    }

    void RegionParser::collectViewPortAnchorSetting(std::u32string_view, std::u32string_view settingValue)
    {
        auto optionalCoordinates = ParserUtil::collectCoordinates(settingValue, ParserUtil::COMMA_C);
        if (!optionalCoordinates.has_value())
            return;

        auto [xCoord, yCoord] = optionalCoordinates.value();

        currentObject->setViewAnchorPort({xCoord, yCoord});
    }

    void RegionParser::collectScrollSetting(std::u32string_view, std::u32string_view settingValue)
    {
        if (ParserUtil::compareU32Strings(settingValue, U"up"))
        {
            currentObject->setScrollValue(Region::Scroll::UP);
        }
    }
}