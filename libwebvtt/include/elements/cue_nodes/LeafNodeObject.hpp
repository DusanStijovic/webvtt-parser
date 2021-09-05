#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECT_HPP_

#include "elements/cue_nodes/NodeObject.hpp"
#include <stdexcept>

namespace webvtt {

class LeafNodeObject : public NodeObject {

 public:
  void appendChild(std::shared_ptr<NodeObject> nodeObject) final ;
  void visitChildren(ICueTreeVisitor &visitor) final ;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECT_HPP_
