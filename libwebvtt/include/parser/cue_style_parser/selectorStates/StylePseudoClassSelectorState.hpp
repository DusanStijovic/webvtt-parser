#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_CLASS_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_CLASS_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/selectorStates/FetchSelectorState.hpp"

namespace webvtt {
class StylePseudoClassSelectorState : public FetchSelectorState {
 public:
  StylePseudoClassSelectorState() = default;

 private:
  void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character) override;
  void preprocessBuffer(StyleSheetParser &parser) override;
  std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) override;
};

} // namespace webvtt

#endif //LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_STYLE_PSEUDO_CLASS_SELECTOR_STATE_HPP_
