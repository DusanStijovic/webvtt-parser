#ifndef LIBWEBVTT_LEAF_NODE_OBJECT_H
#define LIBWEBVTT_LEAF_NODE_OBJECT_H

#include "elements/cue_node_objects/NodeObject.h"
#include <stdexcept>

namespace WebVTT
{

    class LeafNodeObject : public NodeObject
    {

    public:
    
        virtual void appendChild(std::shared_ptr<NodeObject> nodeObject) final override
        {
            throw std::runtime_error("Add Node Object not supported to leaf node in tree");
        }
       
    };

} // namespace WebVTT

#endif
