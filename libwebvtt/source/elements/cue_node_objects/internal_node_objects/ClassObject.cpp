#include "elements/cue_node_objects/internal_node_objects/ClassObject.h"

namespace WebVTT
{
   NodeObject::NodeType ClassObject::getNodeType() const
    {
        return NodeObject::NodeType::CLASS;
    };


} // namespace WebVTT
