#include "elements/style_selectors/pseudo_element_selectors/PseudoElementSelector.hpp"
#include "exceptions/NotImplementedError.hpp"
#include "logger/LoggingUtility.hpp"
#include "utf8.h"

namespace webvtt {
StyleSelector::SelectorType
PseudoElementSelector::getSelectorType() const {
  return StyleSelector::SelectorType::PSEUDO_ELEMENT;
}



std::unique_ptr<StyleSelector> PseudoElementSelector::makeNewPseudoElementSelector(std::u32string_view type) {

  DILOGE("Not implemented pseudo class");
  throw NotImplementedError();
}

} // namespace webvtt
