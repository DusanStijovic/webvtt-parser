#include "elements/style_selectors/CompoundSelector.hpp"
#include "elements/visitors/IStyleSelectorVisitor.hpp"

namespace webvtt
{
    StyleSelector::SelectorType
    CompoundSelector::getSelectorType() const
    {
        return StyleSelector::SelectorType::COMPOUND;
    }
    void CompoundSelector::accept(IStyleSelectorVisitor &visitor) const {
      visitor.visit(*this);
    }


} // namespace webvtt
