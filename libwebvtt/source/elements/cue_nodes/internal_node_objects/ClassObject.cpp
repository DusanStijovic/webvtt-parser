#include "elements/cue_nodes/internal_node_objects/ClassObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt
{
    NodeObject::NodeType ClassObject::getNodeType() const
    {
        return NodeObject::NodeType::CLASS;
    };

    void
    ClassObject::accept(ICueTreeVisitor &visitor) const
    {
      visitor.visit(*this);
    }

} // namespace webvtt
