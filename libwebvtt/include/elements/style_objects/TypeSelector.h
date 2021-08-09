#ifndef LIBWEBVTT_TYPE_SELECTOR_H
#define LIBWEBVTT_TYPE_SELECTOR_H
#include "elements/style_objects/StyleSelectorWithArgument.h"
#include <string>

namespace WebVTT
{
    class TypeSelector : public StyleSelectorWithArgument
    {
    public:
        TypeSelector(std::u32string_view typeName) : StyleSelectorWithArgument)(typename) {}
    };

} // namespace WebVTT

#endif //LIBWEBVTT_TYPE_SELECTOR_H
