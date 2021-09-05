#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_RUBY_TEXT_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_RUBY_TEXT_OBJECT_HPP_

#include "elements/cue_nodes/InternalNodeObject.hpp"

namespace webvtt {

class RubyTextObject : public InternalNodeObject {
 public:
  [[nodiscard]] NodeType getNodeType() const override;
  void processEndToken(std::shared_ptr<NodeObject> &nodeObject,
                       std::stack<std::u32string> &languages,
                       NodeObject::NodeType value) override;
  void accept(ICueTreeVisitor &visitor)  const override;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_RUBY_TEXT_OBJECT_HPP_
