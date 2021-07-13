#include "elements/cue_node_objects/internal_node_objects/ItalicObject.h"

namespace WebVTT
{
   NodeObject::NodeType ItalicObject::getNodeType() const
    {
        return NodeObject::NodeType::ITALIC;
    };


} // namespace WebVTT
