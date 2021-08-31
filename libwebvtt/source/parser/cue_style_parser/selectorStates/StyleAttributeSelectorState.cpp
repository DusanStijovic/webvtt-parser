#include "parser/cue_style_parser/selectorStates/StyleAttributeSelectorState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_selectors/AttributeSelector.h"
#include <tuple>
#include <optional>

namespace WebVTT
{

    AttributeSelector::StringMatchType StyleAttributeSelectorState::getStringMatchType(uint32_t mark)
    {
        AttributeSelector::StringMatchType retValue = AttributeSelector::StringMatchType::EXACT_MATCHING;

        switch (mark)
        {
        case STARTS_WITH_MARK:
            retValue = AttributeSelector::StringMatchType::STARTS_WITH;
            break;
        case ENDS_WITH_MARK:
            retValue = AttributeSelector::StringMatchType::ENDS_WITH;
            break;
        case WHITE_SPACE_SEPERATED_WORDS_MARK:
            retValue = AttributeSelector::StringMatchType::WHITE_SPACE_SEPERATED_WORDS;
            break;
        case CONTAINS_SUBSTR_MARK:
            retValue = AttributeSelector::StringMatchType::CONTAINS_SUBSTR;
            break;
        case EXACT_OR_FOLLOWED_BY_MINUS_MARK:
            retValue = AttributeSelector::StringMatchType::EXACT_OR_FOLLOWED_BY_MINUS;
            break;
        }
        return retValue;
    }

    std::unique_ptr<StyleSelector>
    StyleAttributeSelectorState::makeNewAttributeSelector(StyleSheetParser &parser, std::u32string_view attributeSpecfier,
                                                          std::u32string_view attribute)
    {

        if (attribute.empty())
            parser.setState(StyleState::StyleStateType::ERROR);

        auto split = ParserUtil::splitStringAroundCharacter(attribute, ParserUtil::EQUAL_C);
        AttributeSelector::StringMatchType stringMatchType = AttributeSelector::StringMatchType::UNDEFINED;
        std::u32string_view attributeName, attributeValue;

        if (!split.has_value())
        {
            stringMatchType = AttributeSelector::StringMatchType::NO_VALUE;
            attributeName = attribute;
        }
        else
        {

            attributeName = std::get<0>(split.value());
            attributeValue = std::get<1>(split.value());
            //TODO see if needed
            ParserUtil::strip(attributeName, ParserUtil::isASCIIWhiteSpaceCharacter);
            ParserUtil::strip(attributeValue, ParserUtil::isASCIIWhiteSpaceCharacter);

            if (attributeName.empty())
                parser.setState(StyleState::StyleStateType::ERROR);

            stringMatchType = getStringMatchType(attributeName.back());
            if (stringMatchType == AttributeSelector::StringMatchType::EXACT_MATCHING)
                attributeName.remove_suffix(1);
        }

        std::unique_ptr<AttributeSelector> attributeSelecotr = nullptr;

        if (attributeSpecfier == ParserUtil::VOICE_TYPE_MARK && attributeName == ParserUtil::VOICE_ATRIBUTE_MARK)
        {
            attributeSelecotr = std::make_unique<AttributeSelector>(attributeName, attributeValue);
        }
        if (attributeSpecfier == ParserUtil::LANG_TYPE_MARK && attributeName == ParserUtil::LANG_ATTRIBUTE_MARK)
        {
            attributeSelecotr = std::make_unique<AttributeSelector>(attributeName, attributeValue);
        }
        if (attributeSpecfier.empty() && attributeName == ParserUtil::VOICE_ATRIBUTE_MARK)
        {
            attributeSelecotr = std::make_unique<AttributeSelector>(attributeName, attributeValue);
        }
        if (attributeSpecfier.empty() && attributeName == ParserUtil::LANG_ATTRIBUTE_MARK)
        {
            attributeSelecotr = std::make_unique<AttributeSelector>(attributeName, attributeValue);
        }
        if (attributeSelecotr == nullptr)
            parser.setState(StyleState::StyleStateType::ERROR);
        attributeSelecotr->setStringMatchingType(stringMatchType);
        return attributeSelecotr;
    }

    void

    StyleAttributeSelectorState::preprocessBuffer(StyleSheetParser &parser)
    {
        if (parser.getAdditionalBuffer().size() < 2)
            parser.setState(StyleState::StyleStateType::ERROR);

        if (parser.getAdditionalBuffer().back() != ParserUtil::RIGHT_SQUARE_BRACKET_C)
            parser.setState(StyleState::StyleStateType::ERROR);

        parser.getAdditionalBuffer().pop_back();
    }

    void
    StyleAttributeSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character)
    {
        parser.getAdditionalBuffer().push_back(character);
    }

    std::unique_ptr<StyleSelector>
    StyleAttributeSelectorState::makeNewStyleSelector(StyleSheetParser &parser)
    {

        return makeNewAttributeSelector(parser, parser.getBuffer(), parser.getAdditionalBuffer());
    }

} // namespace WebVTT
