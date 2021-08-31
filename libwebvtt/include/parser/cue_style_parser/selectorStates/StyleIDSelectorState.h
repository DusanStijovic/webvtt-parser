#ifndef LIBWEBVTT_ID_SELECTOR_STATE_H
#define LIBWEBVTT_ID_SELECTOR_STATE_H
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"
namespace WebVTT
{

    class StyleIDSelectorState : public FetchSelectorState
    {
    public:
        StyleIDSelectorState() = default;
     

    private:
        virtual void preprocessBuffer(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_IDSELECTORSTATE_H
