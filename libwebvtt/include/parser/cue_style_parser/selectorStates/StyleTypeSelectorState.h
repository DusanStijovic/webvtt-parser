#ifndef LIBWEBVTT_STYLE_TYPE_SELECTOR_STATE_H
#define LIBWEBVTT_STYLE_TYPE_SELECTOR_STATE_H
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"

namespace WebVTT
{
    class StyleTypeSelectorState : public FetchSelectorState
    {
    public:
        explicit StyleTypeSelectorState() = default;

    private:
        static bool checkIfTypeAllowed(std::u32string typeName);
        void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;

        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
        void preprocessBuffer(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_TYPE_SELECTOR_STATE_H
