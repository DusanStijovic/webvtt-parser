#ifndef LIBWEBVTT_STYLE_PSEUDO_CLASS_SELECTOR_STATE_H
#define LIBWEBVTT_STYLE_PSEUDO_CLASS_SELECTOR_STATE_H
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"

namespace WebVTT
{
    class StylePseudoClassSelectorState : public FetchSelectorState
    {
    public:
        StylePseudoClassSelectorState() = default;

    private:
        virtual void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;
        virtual void preprocessBuffer(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_PSEUDO_CLASS_SELECTOR_STATE_H
