#ifndef LIBWEBVTT_LEAF_NODE_OBJECT_H
#define LIBWEBVTT_LEAF_NODE_OBJECT_H

#include "elements/cue_nodes/NodeObject.h"
#include <stdexcept>

namespace WebVTT
{

    class LeafNodeObject : public NodeObject
    {

    public:
        void appendChild(std::shared_ptr<NodeObject> nodeObject) final override;
        void visitChildren(ICueTreeVisitor &visitor) final override;
    };

} // namespace WebVTT

#endif
