#include "parser/cue_style_parser/states/StylePseudoClassTwoColonState.h"
#include "parser/StyleSheetParser.h"
#include "parser/ParserUtil.h"
#include "elements/style_objects/AttributeSelector.h"

namespace WebVTT {
    void StylePseudoClassTwoColonState::processState() {
        uint32_t character = getNextCharacter();

        if (ParserUtil::isWhiteSpaceCharacter(character))
            return;




        // switch (character) {
        //     case ParserUtil::LEFT_PARENTHESIS_C: {
        //         if (styleSheetParser.getBuffer() != ParserUtil::LANG_TYPE_MARK) {
        //             styleSheetParser.setEndParsing(true);
        //             return;
        //         }
        //         //Mew state for parsing langue
        //     }
        //     case ParserUtil::RIGHT_PARENTHESIS_C: {
        //         auto result = styleSheetParser.getBuffer();
        //         if (result != U"past" && result != U"future") {
        //             styleSheetParser.setEndParsing(true);
        //             return;
        //         }
        //         //TODO Make future/past selector
        //         break;
        //     }
        //     default:
        //         styleSheetParser.getBuffer().push_back(*currentPositioon);
        //         break;
        // }
    }

} // namespace WebVTT
