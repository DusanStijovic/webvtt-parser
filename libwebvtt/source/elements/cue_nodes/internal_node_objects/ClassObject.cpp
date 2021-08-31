#include "elements/cue_nodes/internal_node_objects/ClassObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{
    NodeObject::NodeType ClassObject::getNodeType() const
    {
        return NodeObject::NodeType::CLASS;
    };

    void
    ClassObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
