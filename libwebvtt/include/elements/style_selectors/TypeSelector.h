#ifndef LIBWEBVTT_TYPE_SELECTOR_H
#define LIBWEBVTT_TYPE_SELECTOR_H
#include "elements/style_objects/StyleSelector.h"
#include <string>

namespace WebVTT
{
    class TypeSelector : public StyleSelector
    {
    public:
        TypeSelector(std::u32string_view typeName)
        {
            this->typeName = typeName;
        }
        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;

    private:
        std::u32string typeName;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_TYPE_SELECTOR_H
