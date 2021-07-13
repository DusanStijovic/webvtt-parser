#include "elements/cue_node_objects/internal_node_objects/RubyTextObject.h"

namespace WebVTT
{
    NodeObject::NodeType RubyTextObject::getNodeType() const
    {
        return NodeObject::NodeType::RUBY_TEXT;
    };
    void RubyTextObject::processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages, NodeType value)
    {
        if (value == NodeObject::NodeType::RUBY)
        {
            auto parent = nodeObejct->getParent();
            if (parent == nullptr)
            {
                //TODO Log error
                return;
            }
            auto granparent = parent->getParent();
            if (granparent == nullptr)
            {
                //TODO Log error
                return;
            }
            nodeObejct = granparent;
            return;
        }
        NodeObject::processEndToken(nodeObejct, languages, value);
    };

} // namespace WebVTT
