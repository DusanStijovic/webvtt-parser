#include "elements/cue_node_objects/internal_node_objects/RubyObject.h"

namespace WebVTT
{
     NodeObject::NodeType RubyObject::getNodeType() const
    {
        return NodeObject::NodeType::RUBY;
    };



} // namespace WebVTT
