#include "elements/cue_nodes/internal_node_objects/RubyTextObject.h"
#include "elements/visitors/ICueTreeVisitor.h"
#include "logger/LoggingUtility.h"

namespace WebVTT
{
    NodeObject::NodeType RubyTextObject::getNodeType() const
    {
        return NodeObject::NodeType::RUBY_TEXT;
    };
    void RubyTextObject::processEndToken(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages, NodeType value)
    {
        NodeObject::processEndToken(nodeObject, languages, value);

        if (value == NodeObject::NodeType::RUBY && nodeObject->getNodeType() == NodeObject::NodeType::RUBY_TEXT)
        {
            auto parent = nodeObject->getParent().lock();
            if (parent == nullptr)
            {
                DILOGE("No parrent to ruby text object");
                return;
            }
            auto grandparent = parent->getParent().lock();
            if (grandparent == nullptr)
            {
                DILOGE("No grand parrent to ruby text object");
                return;
            }
            nodeObject = grandparent;
            return;
        }
    };

    void RubyTextObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
