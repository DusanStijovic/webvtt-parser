#include "elements/cue_nodes/internal_node_objects/UnderlineObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt {

NodeObject::NodeType UnderlineObject::getNodeType() const {
  return NodeObject::NodeType::UNDERLINE;
};

void UnderlineObject::accept(ICueTreeVisitor &visitor) const {
  visitor.visit(*this);
}
} // namespace webvtt
