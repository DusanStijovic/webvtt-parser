#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_RUBY_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_RUBY_OBJECT_HPP_

#include "elements/cue_nodes/InternalNodeObject.hpp"

namespace webvtt {

class RubyObject : public InternalNodeObject {
 public:
  [[nodiscard]] NodeType getNodeType() const override;
  void accept(ICueTreeVisitor &visitor) const override;
  void visit(const RubyTypeSelector &selector) override;
};

} // namespace webvtt

#endif //LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_RUBY_OBJECT_HPP_
