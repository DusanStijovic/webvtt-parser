#include "elements/cue_node_objects/leaf_node_objects/TimeStampObject.h"

namespace WebVTT
{
    NodeObject::NodeType TimeStampObject::getNodeType() const
    {
        return NodeObject::NodeType::TIME_STAMP;
    };

} // namespace WebVTT
