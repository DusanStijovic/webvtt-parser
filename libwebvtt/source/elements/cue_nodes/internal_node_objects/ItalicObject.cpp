#include "elements/cue_nodes/internal_node_objects/ItalicObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{
    NodeObject::NodeType ItalicObject::getNodeType() const
    {
        return NodeObject::NodeType::ITALIC;
    };
    
    void
    ItalicObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
