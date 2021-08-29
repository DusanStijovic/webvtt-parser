#ifndef LIBWEBVTT_ID_SELECTOR_H
#define LIBWEBVTT_ID_SELECTOR_H
#include "elements/style_objects/StyleSelector.h"
#include <string>

namespace WebVTT
{
    class IDSelector : public StyleSelector
    {
    public:
        IDSelector(std::u32string_view new_id) : StyleSelector()
        {
            this->id = new_id;
        }
        bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
        SelectorType getSelectorType() const override;

    private:
        std::u32string id;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ID_SELECTOR_H
