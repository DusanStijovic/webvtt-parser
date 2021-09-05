#include "parser/cue_style_parser/selectorStates/StylePseudoClassWithArgumentEndState.hpp"
#include "elements/style_selectors/pseudo_class_selectors/PseudoClassWithArgument.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt {
std::unique_ptr<StyleSelector>
StylePseudoClassWithArgumentEndState::makeNewPseudoStyleSelector(StyleSheetParser &parser) {
  return PseudoClassWithArgument::makeNewPseudoClassWithArgument(parser.getBuffer(), parser.getAdditionalBuffer());
}
} // namespace webvtt
