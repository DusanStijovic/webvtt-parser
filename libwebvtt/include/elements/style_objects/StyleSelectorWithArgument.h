#ifndef LIBWEBVTT_STYLE_SELECTOR_WITH_ARGUMENT_H
#define LIBWEBVTT_STYLE_SELECTOR_WITH_ARGUMENT_H
#include "elements/style_objects/StyleSelector.h"

namespace WebVTT
{
    class StyleSelectorWithArgument : public StyleSelector
    {
    public:
        StyleSelectorWithArgument(std::u32string_view argument) : argument(argument) {}

    protected:
        std::u32string argument;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_SELECTOR_WITH_ARGUMENT_H
