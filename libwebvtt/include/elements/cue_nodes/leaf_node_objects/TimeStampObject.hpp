#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECTS_TIME_STAMP_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECTS_TIME_STAMP_OBJECT_HPP_

#include "elements/cue_nodes/LeafNodeObject.hpp"

namespace webvtt {
class TimeStampObject : public LeafNodeObject {
 public:
  explicit TimeStampObject(double newTime) : time(newTime) {}

  [[nodiscard]] NodeObject::NodeType getNodeType() const override;
  void accept(ICueTreeVisitor &visitor) const override;

 private:
  double time;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECTS_TIME_STAMP_OBJECT_HPP_
