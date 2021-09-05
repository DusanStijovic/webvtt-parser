#include "elements/cue_nodes/NodeObject.hpp"
#include "logger/LoggingUtility.hpp"

namespace webvtt
{
    void NodeObject::setParent(const std::weak_ptr<NodeObject> &newParent)
    {
        this->parent = newParent;
    };

    std::weak_ptr<NodeObject> NodeObject::getParent()
    {
        return this->parent;
    }

    void NodeObject::processEndToken(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages,
                                     NodeType value)
    {
        if (nodeObject->getNodeType() == value)
        {
            auto temp = nodeObject->getParent().lock();
            if (temp != nullptr)
              nodeObject = temp;
        }
        else
        {
            DILOGE("Start tag name and end tag name is not same");
        }
    }

    
    

} //Enf of namespace