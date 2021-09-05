#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_STYLE_SELECTOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_STYLE_SELECTOR_HPP_
#include "elements/rules_filters/RuleFilter.hpp"
#include "elements/cue_nodes/NodeObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"
#include <set>
#include <string>
#include <map>
namespace webvtt {
class StyleSelector : public ICueTreeVisitor {

 public:
  StyleSelector() {
    this->styleSelectorCombinator = StyleSelectorCombinator::NONE;
  };
  enum class SelectorType {
    ID,
    ATTRIBUTE,
    CLASS,
    TYPE,
    PSEUDO_CLASS,
    PSEUDO_ELEMENT,
    MATCH_ALL,
    COMPOUND
  };

  enum class StyleSelectorCombinator {
    UNDEFINED,
    NONE,
    MULTIPLE,
    DESCENDANT,
    CHILD,
    NEXT_SIBLING,
    SUBSEQUENT_SIBLING
  };

  void setStyleSelectorCombinator(StyleSelectorCombinator styleSelectorCombinator);
  [[nodiscard]] StyleSelectorCombinator getStyleSelectorCombinator() const;

  [[nodiscard]] virtual SelectorType getSelectorType() const = 0;

  void connectCue(const Cue &cue);
  void disconnectCue();


  StyleSelector(const StyleSelector &) = delete;
  StyleSelector(StyleSelector &&) = delete;
  StyleSelector &operator=(const StyleSelector &) = delete;
  StyleSelector &operator=(StyleSelector &&) = delete;
  virtual ~StyleSelector() = default;

  void visit(const TimeStampObject &object) override;
  void visit(const TextObject &object) override;

  void visit(const BoldObject &object) override;
  void visit(const ItalicObject &object) override;
  void visit(const ClassObject &object) override;
  void visit(const RubyObject &object) override;
  void visit(const RubyTextObject &object) override;
  void visit(const UnderlineObject &object) override;
  void visit(const VoiceObject &object) override;
  void visit(const LanguageObject &object) override;
  void visit(const RootObject &object) override;

 protected:
  StyleSelectorCombinator styleSelectorCombinator;
  const Cue *connectedCue;
  bool retValue;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_STYLE_SELECTORS_STYLE_SELECTOR_HPP_
