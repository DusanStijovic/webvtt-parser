#include "elements/cue_nodes/leaf_node_objects/TextObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

namespace WebVTT
{
    NodeObject::NodeType TextObject::getNodeType() const
    {
        return NodeObject::NodeType::TEXT;
    };

    void
    TextObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
