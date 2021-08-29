#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/CueParser.h"
#include "parser/ParserUtil.h"
#include "elements/cue_node_objects/NodeObject.h"
#include "elements/cue_node_objects/internal_node_objects/RootObject.h"
#include "logger/LoggingUtility.h"
#include <iostream>
#include <stack>
#include "exceptions/cue_parsing/CueParsingError.h"
#include "exceptions/cue_parsing/CueParsingTimingException.h"
#include "exceptions/parser_util/ParsingFloatPointNumber.h"
#include "exceptions/parser_util/ParsingTimeStampException.h"

namespace WebVTT
{

    bool CueParser::parseTimingAndSettings(std::u32string_view input,
                                           std::u32string_view::iterator &position)
    {
        try
        {
            if (currentObject == nullptr)
                return false;

            this->parseAndSetTiming(input, position, TIME_STAMP_SEPARATOR);

            this->parseAndSetSetting(input, position);
            return true;
        }
        catch (const CueParsingTimingException &error)
        {
            DILOGE(error.what());
        }
        return false;
    }

    void
    CueParser::parseAndSetTiming(std::u32string_view input, std::u32string_view::iterator &position,
                                 std::u32string_view separator)
    {
        try
        {
            ParserUtil::skipWhiteSpaces(input, position);
            if (position == input.end())
                throw CueParsingTimingException();

            double timePoint1 = ParserUtil::parseTimeStamp(input.substr(position - input.begin()), position);
            currentObject->setStartTime(timePoint1);

            ParserUtil::skipWhiteSpaces(input, position);
            if (position == input.end())
                throw CueParsingTimingException();

            std::u32string_view temp = input.substr(position - input.begin(), separator.length());
            if (!ParserUtil::compareU32Strings(separator, temp))
                throw CueParsingTimingException();
            position = position + separator.length();

            ParserUtil::skipWhiteSpaces(input, position);

            double timePoint2 = ParserUtil::parseTimeStamp(input.substr(position - input.begin()), position);
            currentObject->setEndTime(timePoint2);
            return;
        }
        catch (const ParsingTimeStampException &error)
        {
            DILOGE(error.what());
            throw CueParsingTimingException();
        }
    }

    void CueParser::parseAndSetSetting(std::u32string_view input, std::u32string_view::iterator &position)
    {
        std::u32string_view setting;
        std::u32string settingName, settingValue;
        std::u32string characters = {ParserUtil::SPACE_C, ParserUtil::TAB_C};

        while (position != input.end())
        {
            setting = ParserUtil::parseUntilAnyOfGivenCharacters(input, characters, position);
            if (position != input.end())
                position++;

            DILOGI(utf8::utf32to8(setting));

            auto settingInfoOptional = ParserUtil::splitStringAroundCharacter(setting, ParserUtil::COLON_C);

            if (!settingInfoOptional.has_value())
                continue;

            auto [settingName, settingValue] = settingInfoOptional.value();

            if (ParserUtil::compareU32Strings(settingName, REGION_SETTING))
            {
                parseAndSetRegionSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, VERTICAL_SETTING))
            {
                parseAndSetVerticalSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, LINE_SETTING))
            {
                parseAndSetPositionSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, POSITION_SETTING))
            {
                parseAndSetPositionSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, SIZE_SETTING))
            {
                parseAndSetSizeSetting(settingValue);
                continue;
            }
            if (ParserUtil::compareU32Strings(settingName, ALIGN_SETTING))
            {
                parseAndSetAlignSetting(settingValue);
                continue;
            }
        }
    }

    void CueParser::parseAndSetAlignSetting(std::u32string_view value)
    {
        if (ParserUtil::compareU32Strings(value, START_ALIGNMENT))
        {
            currentObject->setTextAlignment(Cue::Alignment::START);
            return;
        }
        if (ParserUtil::compareU32Strings(value, CENTER_ALIGNMENT))
        {
            currentObject->setTextAlignment(Cue::Alignment::CENTER);
            return;
        }
        if (ParserUtil::compareU32Strings(value, END_ALIGNMENT))
        {
            currentObject->setTextAlignment(Cue::Alignment::END);
            return;
        }
        if (ParserUtil::compareU32Strings(value, RIGHT_ALIGNMENT))
        {
            currentObject->setTextAlignment(Cue::Alignment::RIGHT);
            return;
        }
        if (ParserUtil::compareU32Strings(value, LEFT_ALIGNMENT))
        {
            currentObject->setTextAlignment(Cue::Alignment::LEFT);
            return;
        }
    }

    void CueParser::parseAndSetRegionSetting(std::u32string_view value)
    {

        Region *foundRegion = Region::getRegionByIdentifier(currentRegions, value);
        if (foundRegion == nullptr)
            return;
        currentObject->setRegion(foundRegion);
    }

    void CueParser::parseAndSetVerticalSetting(std::u32string_view value)
    {

        Cue::WritingDirection currentWritingDirection = Cue::WritingDirection::HORIZONTAL;
        if (ParserUtil::compareU32Strings(value, VERTICAL_RIGHT_TO_LEFT))
        {
            currentWritingDirection = Cue::WritingDirection::VERTICAL_GROWING_RIGHT;
        }

        if (ParserUtil::compareU32Strings(value, VERTICAL_LEFT_TO_RIGHT))
        {
            currentWritingDirection = Cue::WritingDirection::VERTICAL_GROWING_LEFT;
        }

        currentObject->setWritingDirection(currentWritingDirection);
    }

    void CueParser::parseAndSetPositionSetting(std::u32string_view value)
    {
        try
        {
            std::u32string_view colPos = value, colAlign;

            auto splitStrings = ParserUtil::splitStringAroundCharacter(value, ParserUtil::COMMA_C);
            if (splitStrings.has_value())
            {
                auto [colPosHelp, colAlignHelp] = splitStrings.value();
                colPos = std::move(colPosHelp);
                colAlign = std::move(colAlignHelp);
                if (colAlign.empty() || colAlign.empty())
                {
                    DILOGE("Error while parsing position setting");
                    throw CueParsingError();
                }
            }

            double number = ParserUtil::parsePercentage(colPos);

            if (ParserUtil::compareU32Strings(colAlign, LINE_LEFT))
            {
                currentObject->setPositionAlignment(Cue::Alignment::LEFT);
            }
            else if (ParserUtil::compareU32Strings(colAlign, LINE_CENTER))
            {
                currentObject->setPositionAlignment(Cue::Alignment::CENTER);
            }
            else if (ParserUtil::compareU32Strings(colAlign, LINE_RIGHT))
            {
                currentObject->setPositionAlignment(Cue::Alignment::RIGHT);
            }
            else if (!colAlign.empty())
                return;

            currentObject->setPosition(number);
        }
        catch (const ParsingFloatPointNumber &error)
        {
            DILOGE(error.what());
        }
        catch (const CueParsingError &error)
        {
            DILOGE(error.what());
        }
    }

    void CueParser::parseAndSetLineSetting(std::u32string_view value)
    {
        try
        {
            std::u32string_view linePos = value, lineAlign;
            std::optional<double> optionalNumber;
            double number;

            auto splitStrings = ParserUtil::splitStringAroundCharacter(value, ParserUtil::COMMA_C);
            if (splitStrings.has_value())
            {
                auto [linePosHelp, lineAlignHelp] = splitStrings.value();
                linePos = linePosHelp;
                lineAlign = lineAlignHelp;

                if (linePos.empty() || lineAlign.empty())
                {
                    DILOGE("Line setting not parsed succesffuly");
                    throw CueParsingError();
                }
            }
            auto percentagePos = linePos.find(ParserUtil::PERCENT_C);
            bool percentageOnLastPosition = (percentagePos == linePos.length() - 1);
            bool percentageFound = (percentagePos == std::u32string_view::npos);

            if (percentageFound && !percentageOnLastPosition)
                return;

            if (percentageOnLastPosition)
            {
                number = ParserUtil::parsePercentage(linePos);
            }
            else
            {
                number = ParserUtil::parseFloatPointingNumber(linePos);
            }

            if (ParserUtil::compareU32Strings(lineAlign, START_ALIGNMENT))
            {
                currentObject->setLineAlignment(Cue::Alignment::START);
            }
            else if (ParserUtil::compareU32Strings(lineAlign, CENTER_ALIGNMENT))
            {
                currentObject->setLineAlignment(Cue::Alignment::CENTER);
            }
            else if (ParserUtil::compareU32Strings(lineAlign, END_ALIGNMENT))
            {
                currentObject->setLineAlignment(Cue::Alignment::END);
            }
            else if (!lineAlign.empty())
                return;

            currentObject->setLineNumber(number);

            bool newSnapToLines = true;
            if (percentageOnLastPosition)
            {
                newSnapToLines = false;
            }
            currentObject->setSnapToLines(newSnapToLines);
        }
        catch (const CueParsingError &error)
        {
            DILOGE(error.what());
        }
        catch (const ParsingFloatPointNumber &error)
        {
            DILOGE(error.what());
        }
    }

    void CueParser::parseAndSetSizeSetting(std::u32string_view value)
    {
        try
        {
            double percentage = ParserUtil::parsePercentage(value);
            if (percentage < 0 || percentage > 100)
                return;
            currentObject->setSize(percentage);
        }
        catch (const ParsingFloatPointNumber &error)
        {
            DILOGE(error.what());
        }
    }

    void CueParser::setTextToObject(std::u32string text)
    {
        currentObject->setText(std::move(text));
    }

    void CueParser::parseTextStyleAndMakeStyleTree(std::u32string_view defaultLangage)
    {

        cueTextTokenizer->setText(this->currentObject->getText());
        std::shared_ptr<Token> token = nullptr;

        std::stack<std::u32string> languages;

        std::shared_ptr<NodeObject> root = std::make_shared<RootObject>();

        std::shared_ptr<NodeObject> currentNode = root;

        if (!defaultLangage.empty())
            languages.push(std::u32string(defaultLangage));

        while (cueTextTokenizer->getCurrentPosition() != cueTextTokenizer->getInput().end())
        {

            token = cueTextTokenizer->getNextToken();
            token->process(currentNode, languages);
        }
        currentObject->setTextTreeRoot(root);
    };

} // end of namespace