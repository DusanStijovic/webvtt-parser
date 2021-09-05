#include "elements/style_selectors/pseudo_class_selectors/PseudoClassWithArgument.hpp"
#include "logger/LoggingUtility.hpp"
#include "exceptions/NotImplementedError.hpp"

namespace webvtt {

std::unique_ptr<StyleSelector> webvtt::PseudoClassWithArgument::makeNewPseudoClassWithArgument(
    std::u32string_view type, std::u32string_view value) {
  DILOGE("Not implemented pseudo class");
  throw NotImplementedError();
}
} // namespace webvtt


