#ifndef LIBWEBVTT_STYLE_ATTRIBUTE_SELECTOR_STATE_H
#define LIBWEBVTT_STYLE_ATTRIBUTE_SELECTOR_STATE_H

#include "parser/cue_style_parser/selectorStates/FetchSelectorState.h"
#include "elements/style_selectors/AttributeSelector.h"
#include <string>

namespace WebVTT
{

    class StyleAttributeSelectorState : public FetchSelectorState
    {
    public:
        StyleAttributeSelectorState() = default;

    private:
        constexpr static uint32_t STARTS_WITH_MARK = U'^';
        constexpr static uint32_t ENDS_WITH_MARK = U'$';
        constexpr static uint32_t CONTAINS_SUBSTR_MARK = U'*';
        constexpr static uint32_t WHITE_SPACE_SEPERATED_WORDS_MARK = U'~';
        constexpr static uint32_t EXACT_OR_FOLLOWED_BY_MINUS_MARK = U'|';

        static AttributeSelector::StringMatchType getStringMatchType(uint32_t mark);

        void preprocessBuffer(StyleSheetParser &parser) override;

        void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;

        std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;

        std::unique_ptr<StyleSelector>
        makeNewAttributeSelector(StyleSheetParser &parser, std::u32string_view attributeSpecfier, std::u32string_view attribut);
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_ATTRIBUTE_SELECTOR_STATE_H
