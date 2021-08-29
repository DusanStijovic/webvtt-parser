#include "elements/cue_node_objects/NodeObject.h"
#include "logger/LoggingUtility.h"

namespace WebVTT
{
    void NodeObject::setParent(const std::weak_ptr<NodeObject> &newParent)
    {
        this->parent = newParent;
    };

    std::weak_ptr<NodeObject> NodeObject::getParent()
    {
        return this->parent;
    }

    void NodeObject::processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages,
                                     NodeType value)
    {
        if (nodeObejct->getNodeType() == value)
        {
            auto temp = nodeObejct->getParent().lock();
            if (temp != nullptr)
                nodeObejct = temp;
        }
        else
        {
            DILOGE("Start tag name and end tag name is not same");
        }
    }

} //Enf of namespace