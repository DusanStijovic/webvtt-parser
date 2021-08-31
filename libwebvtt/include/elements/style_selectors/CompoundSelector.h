#ifndef LIBWEBVTT_COMPOUNDSELECTOR_H
#define LIBWEBVTT_COMPOUNDSELECTOR_H
#include "elements/style_selectors/StyleSelector.h"
#include <list>

namespace WebVTT {
class CompoundSelector : public StyleSelector {
 public:
  CompoundSelector(std::list<std::unique_ptr<StyleSelector>> &&newStyleSelectors) {
    this->styleSelectors = std::move(newStyleSelectors);
  }
  bool shouldApply(const NodeObject &nodeObject, const Cue &cue) const override;
  SelectorType getSelectorType() const override;

 private:
  std::list<std::unique_ptr<StyleSelector>> styleSelectors;
};

} // namespace WebVTT

#endif //LIBWEBVTT_COMPOUNDSELECTOR_H
