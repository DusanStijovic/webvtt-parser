#include "elements/cue_node_objects/NodeObject.h"

namespace WebVTT
{
    void NodeObject::setParent(const std::shared_ptr<NodeObject> &newParent)
    {
        this->parent = newParent;
    };

    std::shared_ptr<NodeObject> NodeObject::getParent()
    {
        return this->parent;
    }

    void NodeObject::processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages, NodeType value)
    {
        if (nodeObejct->getNodeType() == value)
        {
            if (nodeObejct->getParent() != nullptr)
                nodeObejct = nodeObejct->getParent();
            else
            {
                //Log error and continue;
            }
        }
        else
        {
            //Log error and continue;
        }
    }

} //Enf of namespace