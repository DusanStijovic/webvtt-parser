#include "elements/cue_nodes/leaf_node_objects/TimeStampObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt {
NodeObject::NodeType TimeStampObject::getNodeType() const {
  return NodeObject::NodeType::TIME_STAMP;
};
void
TimeStampObject::accept(ICueTreeVisitor &visitor) const  {
  visitor.visit(*this);
}

} // namespace webvtt
