#include "elements/cue_nodes/internal_node_objects/BoldObject.h"
#include "elements/visitors/ICueTreeVisitor.h"
namespace WebVTT
{
    NodeObject::NodeType BoldObject::getNodeType() const
    {
        return NodeObject::NodeType::BOLD;
    };

    void
    BoldObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
