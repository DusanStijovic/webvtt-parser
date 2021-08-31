#ifndef STYLE_PSEUDO_ELEMENT_SELECTOR_STATE_H
#define STYLE_PSEUDO_ELEMENT_SELECTOR_STATE_H
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"
#include "elements/style_selectors/StyleSelector.h"

namespace WebVTT
{
    class StylePseudoElementSelectorState : public FetchSelectorState
    {
    public:
        StylePseudoElementSelectorState() = default;

    private:
        void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;
        void preprocessBuffer(StyleSheetParser &parser) override;
        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif // STYLE_PSEUDO_ELEMENT_SELECTOR_STATE_H