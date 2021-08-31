#ifndef FETCH_SELECTOR_STATE_H
#define FETCH_SELECTOR_STATE_H
#include "parser/cue_style_parser/states/StyleState.h"
#include "elements/style_selectors/StyleSelector.h"

namespace WebVTT
{

    class FetchSelectorState : public StyleState
    {
    public:
        FetchSelectorState() = default;
        void processState(StyleSheetParser &parser) override;

    protected:
        virtual void foundStopTokenizer(StyleSheetParser &parser);
        virtual void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character);

        virtual void foundCommaCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);
        virtual void foundCombinatorCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);
        virtual void foundCompoundCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);
        virtual void foundRightParenthes(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);

        virtual void foundCommaCharacter(StyleSheetParser &parser);
        virtual void foundCombinatorCharacter(StyleSheetParser &parser, StyleSelector::StyleSelectorCombinator styleCombinator);
        virtual void foundCompoundCharacter(StyleSheetParser &parser);
        virtual void foundRightParenthes(StyleSheetParser &parser);

        virtual bool additionalBehaviour(StyleSheetParser &parser, uint32_t character);

        virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser);
        virtual void preprocessBuffer(StyleSheetParser &parser);
    };

} // namespace WebVTT

#endif // FETCH_SELECTOR_STATE_H