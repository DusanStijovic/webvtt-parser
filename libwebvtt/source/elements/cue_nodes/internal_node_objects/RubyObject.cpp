#include "elements/cue_nodes/internal_node_objects/RubyObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt {
NodeObject::NodeType RubyObject::getNodeType() const {
  return NodeObject::NodeType::RUBY;
};
void
RubyObject::accept(ICueTreeVisitor &visitor) const  {
  visitor.visit(*this);
}

} // namespace webvtt
