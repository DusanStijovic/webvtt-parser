#ifndef LIBWEBVTT_CLASS_SELECTOR_H
#define LIBWEBVTT_CLASS_SELECTOR_H
#include "elements/style_objects/StyleSelectorWithArgument.h"
#include <string>

namespace WebVTT
{

    class ClassSelector : public StyleSelectorWithArgument
    {
    public:
        ClassSelector(std::u32string_view className) : StyleSelectorWithArgument(className)
        {
        }
    };

} // namespace WebTT

#endif //LIBWEBVTT_CLASS_SELECTOR_H
