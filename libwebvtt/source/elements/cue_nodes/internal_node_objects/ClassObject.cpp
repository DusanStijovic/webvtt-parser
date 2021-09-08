#include "elements/cue_nodes/internal_node_objects/ClassObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt {
NodeObject::NodeType ClassObject::getNodeType() const {
  return NodeObject::NodeType::CLASS;
};

void
ClassObject::accept(ICueTreeVisitor &visitor) const {
  visitor.visit(*this);
}

void ClassObject::visit(const ClassTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = true;
}

} // namespace webvtt
