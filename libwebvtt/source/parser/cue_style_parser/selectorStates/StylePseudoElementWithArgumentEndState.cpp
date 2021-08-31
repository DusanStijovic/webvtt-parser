#include "parser/cue_style_parser/selectorStates/StylePseudoElementWithArgumentEndState.h"
#include "elements/style_selectors/PseudoElementSelector.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
{
    std::unique_ptr<StyleSelector>
    StylePseudoElementWithArgumentEndState::makeNewPseudoStyleSelector(StyleSheetParser &parser)
    {
        return std::make_unique<PseudoElementSelector>(parser.getBuffer(), parser.getAdditionalBuffer());
    }
} // namespace WebVTT
