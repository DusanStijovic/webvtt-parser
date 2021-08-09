#include "elements/StyleSheet.h"

namespace WebVTT
{
    void StyleSheet::setSelector(const std::shared_ptr<StyleSelector> &new_selector)
    {
        this->styleSelector = new_selector;
    }
} // namespace WebVTT
