#ifndef STYLE_PSEUDO_WITH_ARGUMENT_END_STATE_H
#define STYLE_PSEUDO_WITH_ARGUMENT_END_STATE_H
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"

namespace WebVTT
{
    class StylePseudoWithArgumentEndState : public FetchSelectorState
    {
    public:
        StylePseudoWithArgumentEndState() = default;
        void preprocessBuffer(StyleSheetParser &parser) override;
        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewPseudoStyleSelector(StyleSheetParser &parser) = 0;
    };

} // namespace WebVTT

#endif //STYLE_PSEUDO_WITH_ARGUMENT_END_STATE_H