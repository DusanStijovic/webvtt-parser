#include "elements/cue_node_objects/internal_node_objects/RootObject.h"

namespace WebVTT
{

    NodeObject::NodeType RootObject::getNodeType() const
    {
        return NodeObject::NodeType::ROOT;
    };

} // namespace WebVTT
