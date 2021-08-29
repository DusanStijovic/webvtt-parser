#ifndef LIBWEBVTT_ATTRIBUTE_SELECTOR_H
#define LIBWEBVTT_ATTRIBUTE_SELECTOR_H
#include "elements/style_objects/StyleSelector.h"

namespace WebVTT
{

    class AttributeSelector : public StyleSelector
    {
    public:
        AttributeSelector(std::u32string_view name, std::u32string_view value)
        {
            this->attributeName = name;
            this->attributeValue = value;
        }
        enum class StringMatchType
        {
            UNDEFINED,
            NO_VALUE,
            EXACT_MATCHING,
            STARTS_WITH,
            ENDS_WITH,
            CONTAINS_SUBSTR,
            WHITE_SPACE_SEPERATED_WORDS,
            EXACT_OR_FOLLOWED_BY_MINUS

        };
        void setStringMatchingType(StringMatchType stringMatchType);
        StringMatchType getStringMatchingType() const;
        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;

    protected:
        std::u32string attributeName;
        std::u32string attributeValue;

    private:
        StringMatchType stringMatchType;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ATTRIBUTE_SELECTOR_H
