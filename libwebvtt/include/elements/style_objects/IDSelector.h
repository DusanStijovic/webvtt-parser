#ifndef LIBWEBVTT_IDSELECTOR_H
#define LIBWEBVTT_IDSELECTOR_H
#include "elements/style_objects/StyleSelectorWithArgument.h"
#include <string>

namespace WebVTT
{
    class IDSelector : public StyleSelectorWithArgument
    {
    public:
        IDSelector(std::u32string_view id) : StyleSelectorWithArgument(id) {}
    };

} // namespace WebVTT

#endif //LIBWEBVTT_IDSELECTOR_H
