#ifndef LIBWEBVTT_STYLE_SELECTOR_H
#define LIBWEBVTT_STYLE_SELECTOR_H
#include <set>
#include <string>

namespace WebVTT
{
    class StyleSelector
    {

    public:
        StyleSelector() = default;
        virtual ~StyleSelector() = 0;

    protected:
    };

} // namespace WebVTT

#endif //LIBWEBVTT_STYLE_SELECTOR_H
