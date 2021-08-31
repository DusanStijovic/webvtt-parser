#ifndef LIB_WEBVTT_CLASS_SELECTOR_STATE_H
#define LIB_WEBVTT_CLASS_SELECTOR_STATE_H
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"
namespace WebVTT
{

    class StyleClassSelectorState : public FetchSelectorState
    {
    public:
        StyleClassSelectorState() = default;
      

    private:
        virtual void preprocessBuffer(StyleSheetParser &parser) override;
        virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
    };

}

#endif //LIB_WEBVTT_CLASS_SELECTOR_STATE_H
