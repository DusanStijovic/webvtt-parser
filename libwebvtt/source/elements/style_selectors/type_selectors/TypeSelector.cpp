#include "elements/style_selectors/type_selectors/TypeSelector.hpp"
#include "elements/style_selectors/type_selectors/BoldTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/ItalicTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/LanguageTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/ClassTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/RubyTextTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/RubyTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/VoiceTypeSelector.hpp"
#include "elements/style_selectors/type_selectors/UnderlineTypeSelector.hpp"
#include "parser/CSSConstants.hpp"

namespace webvtt {
StyleSelector::SelectorType
TypeSelector::getSelectorType() const {
  return StyleSelector::SelectorType::TYPE;
}


std::unique_ptr <StyleSelector> TypeSelector::makeNewTypeSelector(std::u32string_view type) {
  if (type == CSSConstants::VOICE_TYPE) {
    return std::make_unique<VoiceTypeSelector>();
  }
  if (type == CSSConstants::LANG_TYPE) {
    return std::make_unique<LanguageTypeSelector>();
  }
  if (type == CSSConstants::BOLD_TYPE) {
    return std::make_unique<BoldTypeSelector>();
  }
  if (type == CSSConstants::ITALIC_TYPE) {
    return std::make_unique<ItalicTypeSelector>();
  }
  if (type == CSSConstants::UNDERLINE_TYPE) {
    return std::make_unique<UnderlineTypeSelector>();
  }
  if (type == CSSConstants::RUBY_TYPE) {
    return std::make_unique<RubyTypeSelector>();
  }
  if (type == CSSConstants::RUBY_TEXT_TYPE) {
    return std::make_unique<RubyTextTypeSelector>();
  }
  if (type == CSSConstants::CLASS_TYPE) {
    return std::make_unique<ClassTypeSelector>();
  }
  return nullptr;
}

} // namespace webvtt
