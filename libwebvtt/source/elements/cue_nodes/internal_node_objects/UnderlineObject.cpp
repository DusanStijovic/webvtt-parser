#include "elements/cue_nodes/internal_node_objects/UnderlineObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{

    NodeObject::NodeType UnderlineObject::getNodeType() const
    {
        return NodeObject::NodeType::UNDERLINE;
    };


    void UnderlineObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }
} // namespace WebVTT
