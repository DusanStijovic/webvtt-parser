#include "elements/cue_nodes/internal_node_objects/RootObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"
#include "elements/style_selectors/IdSelector.hpp"

namespace webvtt {

NodeObject::NodeType RootObject::getNodeType() const {
  return NodeObject::NodeType::ROOT;
};

void
RootObject::accept(ICueTreeVisitor &visitor) const {
  visitor.visit(*this);
}
std::u32string_view RootObject::getCueId() const {
  return cueId;
}
void RootObject::setCueId(std::u32string_view newCueId) {
  this->cueId = newCueId;
}
void RootObject::visit(const IdSelector &selector) {
  shouldApplyLastVisitedStyleSheet = (selector.getId() == this->cueId);
}
void RootObject::visit(const LanguageSelector &selector) {
  shouldApplyLastVisitedStyleSheet = selector.isValueMatch(this->language);
}

} // namespace webvtt
