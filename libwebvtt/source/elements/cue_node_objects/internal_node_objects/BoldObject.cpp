#include "elements/cue_node_objects/internal_node_objects/BoldObject.h"
namespace WebVTT
{
    NodeObject::NodeType BoldObject::getNodeType() const
    {
        return NodeObject::NodeType::BOLD;
    };

} // namespace WebVTT
