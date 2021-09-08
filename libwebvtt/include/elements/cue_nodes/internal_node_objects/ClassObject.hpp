#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_CLASS_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_CLASS_OBJECT_HPP_

#include "elements/cue_nodes/InternalNodeObject.hpp"

namespace webvtt {

class ClassObject : public InternalNodeObject {
 public:
  virtual NodeType getNodeType() const override;
  void accept(ICueTreeVisitor &visitor) const override;
  void visit(const ClassTypeSelector &selector) override;

};
} // namespace webvtt

#endif //LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_CLASS_OBJECT_HPP_
