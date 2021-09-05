#include "elements/cue_nodes/internal_node_objects/ItalicObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt
{
    NodeObject::NodeType ItalicObject::getNodeType() const
    {
        return NodeObject::NodeType::ITALIC;
    };
    
    void
    ItalicObject::accept(ICueTreeVisitor &visitor) const
    {
      visitor.visit(*this);
    }

} // namespace webvtt
