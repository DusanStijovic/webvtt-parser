#include "elements/cue_node_objects/internal_node_objects/UnderlineObject.h"

namespace WebVTT
{

    NodeObject::NodeType UnderlineObject::getNodeType() const
    {
        return NodeObject::NodeType::UNDERLINE;
    };

} // namespace WebVTT
