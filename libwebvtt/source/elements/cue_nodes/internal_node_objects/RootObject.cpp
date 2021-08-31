#include "elements/cue_nodes/internal_node_objects/RootObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{

    NodeObject::NodeType RootObject::getNodeType() const
    {
        return NodeObject::NodeType::ROOT;
    };

    void
    RootObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
