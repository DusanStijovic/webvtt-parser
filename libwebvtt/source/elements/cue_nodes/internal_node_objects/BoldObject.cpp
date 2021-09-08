#include "elements/cue_nodes/internal_node_objects/BoldObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"
namespace webvtt {
NodeObject::NodeType BoldObject::getNodeType() const {
  return NodeObject::NodeType::BOLD;
};

void
BoldObject::accept(ICueTreeVisitor &visitor) const {
  visitor.visit(*this);
}

void BoldObject::visit(const BoldTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = true;
}

} // namespace webvtt
