#include "parser/cue_style_parser/selectorStates/StyleCollectPseudoClassArgument.h"
#include "parser/ParserUtil.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{
    void
    StyleCollectPseudoArgument::processState(StyleSheetParser &parser)
    {
        uint32_t character = getNextCharacter();
        switch (character)
        {
        case ParserUtil::RIGHT_PARENTHESIS_C:
            parser.goToSavedPseudoState();
            break;
        default:
            parser.getAdditionalBuffer().push_back(character);
            break;
        }
    }
} // namespace WebVTT
