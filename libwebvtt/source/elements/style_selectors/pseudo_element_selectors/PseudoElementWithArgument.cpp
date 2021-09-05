#include "elements/style_selectors/pseudo_element_selectors/PseudoElementWithArgument.hpp"
#include "exceptions/NotImplementedError.hpp"
#include "logger/LoggingUtility.hpp"

namespace webvtt {
std::unique_ptr<StyleSelector> webvtt::PseudoElementWithArgument::makeNewPseudoElementWithArgument(
    std::u32string_view type,
    std::u32string_view value) {
  DILOGE("Not implemented pseudo class");
  throw NotImplementedError();
}

} // namespace webvtt
