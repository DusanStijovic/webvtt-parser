#include "parser/cue_style_parser/selectorStates/StyleTypeSelectorState.h"
#include "elements/style_selectors/TypeSelector.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "parser/CSSConstants.h"

namespace WebVTT
{

    bool StyleTypeSelectorState::checkIfTypeAllowed(std::u32string typeName)
    {
        if (typeName == CSSConstants::BOLD)
            return true;
        if (typeName == CSSConstants::ITALIC)
            return true;
        if (typeName == CSSConstants::CLASS)
            return true;
        if (typeName == CSSConstants::LANG)
            return true;
        if (typeName == CSSConstants::UNDERLINE)
            return true;
        if (typeName == CSSConstants::VOICE)
            return true;
        if (typeName == CSSConstants::RUBY)
            return true;
        if (typeName == CSSConstants::RUBY_TEXT)
            return true;
        return false;
    }

    void
    StyleTypeSelectorState::preprocessBuffer(StyleSheetParser &parser)
    {
        if (parser.getBuffer().empty())
            parser.setState(StyleState::StyleStateType::ERROR);

        if (!checkIfTypeAllowed(parser.getBuffer()))
            parser.setState(StyleState::StyleStateType::ERROR);
    }

    std::unique_ptr<StyleSelector>
    StyleTypeSelectorState::makeNewStyleSelector(StyleSheetParser &parser)
    {
        auto help = std::make_unique<TypeSelector>(parser.getBuffer());
        parser.getBuffer().clear();
        return help;
    }

    void StyleTypeSelectorState::foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character)
    {
        if (character == ParserUtil::LEFT_SQUARE_BRACKET_C)
        {
            parser.setState(StyleState::StyleStateType::ATTRIBUTE_SELECTOR);
        }
        else
        {
            FetchSelectorState::foundDefaultBehaviour(parser, character);
        }
    }

} // namespace WebVTT
