#include "elements/cue_nodes/internal_node_objects/RootObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt
{

    NodeObject::NodeType RootObject::getNodeType() const
    {
        return NodeObject::NodeType::ROOT;
    };

    void
    RootObject::accept(ICueTreeVisitor &visitor) const
    {
      visitor.visit(*this);
    }

} // namespace webvtt
