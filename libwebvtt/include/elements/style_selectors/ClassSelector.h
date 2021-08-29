#ifndef LIBWEBVTT_CLASS_SELECTOR_H
#define LIBWEBVTT_CLASS_SELECTOR_H
#include "elements/style_objects/StyleSelector.h"
#include <string>

namespace WebVTT
{

    class ClassSelector : public StyleSelector
    {
    public:
        ClassSelector(std::u32string_view className) : StyleSelector()
        {
            this->className = className;
        }
        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;

    private:
        std::u32string className;
    };

} // namespace WebTT

#endif //LIBWEBVTT_CLASS_SELECTOR_H
