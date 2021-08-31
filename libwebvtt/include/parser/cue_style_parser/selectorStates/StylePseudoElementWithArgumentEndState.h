#ifndef STYLE_PSEUDO_ELEMENT_WITH_ARGUMENT_END_STATE_H
#define STYLE_PSEUDO_ELEMENT_WITH_ARGUMENT_END_STATE_H
#include "parser/cue_style_parser/selectorStates/StylePseudoWithArgumentEndState.h"

namespace WebVTT
{
    class StylePseudoElementWithArgumentEndState : public StylePseudoWithArgumentEndState
    {
    public:
        StylePseudoElementWithArgumentEndState() = default;
        std::unique_ptr<StyleSelector> makeNewPseudoStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif //STYLE_PSEUDO_CLASS_WITH_ARGUMENT_END_STATE_H