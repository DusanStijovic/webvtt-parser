#include "elements/cue_nodes/LeafNodeObject.hpp"

namespace webvtt
{
    void LeafNodeObject::appendChild(std::shared_ptr<NodeObject> nodeObject)
    {
        throw std::runtime_error("Add Node Object not supported to leaf node in tree");
    }

    void LeafNodeObject::visitChildren(ICueTreeVisitor &visitor)
    {
        throw std::runtime_error("Visit children not supported to leaf node in tree");
    }
} // namespace webvtt
