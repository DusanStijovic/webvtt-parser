#include "elements/cue_nodes/leaf_node_objects/TimeStampObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{
    NodeObject::NodeType TimeStampObject::getNodeType() const
    {
        return NodeObject::NodeType::TIME_STAMP;
    };
    void
    TimeStampObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
