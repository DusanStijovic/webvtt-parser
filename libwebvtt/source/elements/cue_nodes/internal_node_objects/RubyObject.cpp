#include "elements/cue_nodes/internal_node_objects/RubyObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{
    NodeObject::NodeType RubyObject::getNodeType() const
    {
        return NodeObject::NodeType::RUBY;
    };
    void
    RubyObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
