#ifndef LIBWEBVTT_ATTRIBUTE_SELECTOR_H
#define LIBWEBVTT_ATTRIBUTE_SELECTOR_H
#include "elements/style_objects/TypeSelector.h"

namespace WebVTT
{

    class AttributeSelector : public TypeSelector
    {
    public:
        AttributeSelector(std::u32string_view new_attribute_name, std::u32string_view new_attribute_value)
            : TypeSelector(new_attribute_name), attribute_value(new_attribute_value)
        {
        }

    protected:
        std::u32string attribute_value;
        };

} // namespace WebVTT

#endif //LIBWEBVTT_ATTRIBUTE_SELECTOR_H
