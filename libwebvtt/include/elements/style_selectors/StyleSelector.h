#ifndef LIBWEBVTT_STYLE_SELECTOR_H
#define LIBWEBVTT_STYLE_SELECTOR_H
#include "elements/rules_filter_objects/RuleFilter.h"
#include "elements/cue_node_objects/NodeObject.h"
#include <set>
#include <string>
#include <map>
namespace WebVTT
{
    class StyleSelector
    {

    public:
        StyleSelector()
        {
            this->styleSelectorCombinator = StyleSelectorCombinator::NONE;
        };
        virtual ~StyleSelector() = 0;
        enum class SelectorType
        {
            ID,
            ATTRIBUTE,
            CLASS,
            TYPE,
            PSEUDO_CLASS,
            PSEUDO_ELEMENT,
            MATCH_ALL,
            COMPOUND
        };

        enum class StyleSelectorCombinator
        {
            UNDEFINED,
            NONE,
            MULTIPLE,
            DESCENDANT,
            CHILD,
            NEXT_SIBLING,
            SUBSEQUENT_SIBLING
        };

        void setStyleSelectorCombinator(StyleSelectorCombinator styleSelectorCombinator);
        StyleSelectorCombinator getStyleSelectorCombinator() const;
        virtual bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const = 0;
        virtual SelectorType getSelectorType() const = 0;

    private:
        StyleSelectorCombinator styleSelectorCombinator;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_SELECTOR_H
