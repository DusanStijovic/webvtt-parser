#include "elements/cue_nodes/leaf_node_objects/TextObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt
{
    NodeObject::NodeType TextObject::getNodeType() const
    {
        return NodeObject::NodeType::TEXT;
    };

    void
    TextObject::accept(ICueTreeVisitor &visitor) const
    {
      visitor.visit(*this);
    }

} // namespace webvtt
