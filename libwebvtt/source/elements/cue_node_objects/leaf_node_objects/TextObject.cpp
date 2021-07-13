#include "elements/cue_node_objects/leaf_node_objects/TextObject.h"

namespace WebVTT
{
    NodeObject::NodeType TextObject::getNodeType() const
    {
        return NodeObject::NodeType::TEXT;
    };
} // namespace WebVTT
