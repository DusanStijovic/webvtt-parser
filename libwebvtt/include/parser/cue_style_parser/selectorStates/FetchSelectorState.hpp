#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_FETCH_SELECTOR_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_FETCH_SELECTOR_STATE_HPP_
#include "parser/cue_style_parser/states/StyleState.hpp"
#include "elements/style_selectors/StyleSelector.hpp"

namespace webvtt {

class FetchSelectorState : public StyleState {
 public:
  FetchSelectorState() = default;
  void processState(StyleSheetParser &parser) override;

 protected:
  virtual void foundStopTokenizer(StyleSheetParser &parser);
  virtual void foundDefaultBehaviour(StyleSheetParser &parser, uint32_t character);

  virtual void foundCommaCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);
  virtual void foundCombinatorCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);
  virtual void foundCompoundCharacter(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);
  virtual void foundRightParenthesis(StyleSheetParser &parser, std::unique_ptr<StyleSelector> &&styleSelector);

  virtual void foundCommaCharacter(StyleSheetParser &parser);
  virtual void foundCombinatorCharacter(StyleSheetParser &parser,
                                        StyleSelector::StyleSelectorCombinator styleCombinator);
  virtual void foundCompoundCharacter(StyleSheetParser &parser);
  virtual void foundRightParenthesis(StyleSheetParser &parser);

  virtual bool additionalBehaviour(StyleSheetParser &parser, uint32_t character);

  virtual std::unique_ptr<StyleSelector> makeNewStyleSelector(StyleSheetParser &parser) = 0;
  virtual void preprocessBuffer(StyleSheetParser &parser) = 0;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_SELECTOR_STATES_FETCH_SELECTOR_STATE_HPP_