#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECTS_TEXT_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECTS_TEXT_OBJECT_HPP_

#include "elements/cue_nodes/LeafNodeObject.hpp"

namespace webvtt {
class TextObject : public LeafNodeObject {
 public:
  TextObject(std::u32string_view input) {
    this->text = input;
  }
  NodeObject::NodeType getNodeType() const override;
  void accept(ICueTreeVisitor &visitor) const override;

 private:
  std::u32string text;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_LEAF_NODE_OBJECTS_TEXT_OBJECT_HPP_
