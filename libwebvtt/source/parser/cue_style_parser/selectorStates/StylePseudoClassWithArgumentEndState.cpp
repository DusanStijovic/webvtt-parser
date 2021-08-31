#include "parser/cue_style_parser/selectorStates/StylePseudoClassWithArgumentEndState.h"
#include "elements/style_selectors/PseudoClassSelector.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{
    std::unique_ptr<StyleSelector>
    StylePseudoClassWithArgumentEndState::makeNewPseudoStyleSelector(StyleSheetParser &parser)
    {
        return std::make_unique<PseudoClassSelector>(parser.getBuffer(), parser.getAdditionalBuffer());
    }
} // namespace WebVTT
