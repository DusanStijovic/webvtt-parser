#include "parser/cue_style_parser/selectorStates/StylePseudoElementWithArgumentEndState.hpp"
#include "elements/style_selectors/pseudo_element_selectors/PseudoElementWithArgument.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt {
std::unique_ptr<StyleSelector>
StylePseudoElementWithArgumentEndState::makeNewPseudoStyleSelector(StyleSheetParser &parser) {
  return PseudoElementWithArgument::makeNewPseudoElementWithArgument(
      parser.getBuffer(), parser.getAdditionalBuffer());
}
} // namespace webvtt
