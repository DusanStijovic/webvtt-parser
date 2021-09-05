#include "elements/style_selectors/pseudo_class_selectors/PseudoClassSelector.hpp"
#include "exceptions/NotImplementedError.hpp"
#include "logger/LoggingUtility.hpp"
#include "utf8.h"

namespace webvtt {

StyleSelector::SelectorType
PseudoClassSelector::getSelectorType() const {
  return StyleSelector::SelectorType::PSEUDO_CLASS;
}


std::unique_ptr<StyleSelector> PseudoClassSelector::makeNewPseudoClassSelector(std::u32string_view type) {

  DILOGE("Not implemented pseudo class");
  throw NotImplementedError();
}
} // namespace webvtt
