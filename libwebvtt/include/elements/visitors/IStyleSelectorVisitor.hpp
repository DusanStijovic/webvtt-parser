#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_I_STYLE_SELECTOR_VISITOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_I_STYLE_SELECTOR_VISITOR_HPP_
#include "elements/style_selectors/MatchAllSelector.hpp"
#include "elements/style_selectors/ClassSelector.hpp"
#include "elements/style_selectors/CompoundSelector.hpp"
#include "elements/style_selectors/CombinatorSelector.hpp"
#include "elements/style_selectors/IdSelector.hpp"
#include "elements/style_selectors/type_selectors/BoldTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/ClassTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/ItalicTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/LanguageTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/RubyTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/RubyTextTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/UnderlineTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/VoiceTypeSelector.hpp"
#include "elements/style_selectors/attribute_selectors/LanguageSelector.hpp"
#include "elements/style_selectors/attribute_selectors/VoiceSelector.hpp"

namespace webvtt {

class IStyleSelectorVisitor {

 public:

  virtual void visit(const MatchAllSelector &selector) = 0;
  virtual void visit(const IdSelector &selector) = 0;
  virtual void visit(const ClassSelector &selector) = 0;

  virtual void visit(const CompoundSelector &selector) = 0;
  virtual void visit(const CombinatorSelector &selector) = 0;

  virtual void visit(const BoldTypeSelector &selector) = 0;
  virtual void visit(const ClassTypeSelector &selector) = 0;
  virtual void visit(const ItalicTypeSelector &selector) = 0;
  virtual void visit(const LanguageTypeSelector &selector) = 0;
  virtual void visit(const RubyTypeSelector &selector) = 0;
  virtual void visit(const RubyTextTypeSelector &selector) = 0;
  virtual void visit(const UnderlineTypeSelector &selector) = 0;
  virtual void visit(const VoiceTypeSelector &selector) = 0;

  virtual void visit(const LanguageSelector &selector) = 0;
  virtual void visit(const VoiceSelector &selector) = 0;

};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_I_STYLE_SELECTOR_VISITOR_HPP_
