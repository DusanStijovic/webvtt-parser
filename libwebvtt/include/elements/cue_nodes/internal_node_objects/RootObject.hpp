#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_ROOT_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_ROOT_OBJECT_HPP_

#include "elements/cue_nodes/InternalNodeObject.hpp"

namespace webvtt {
class RootObject : public InternalNodeObject {
 public:
  [[nodiscard]] NodeType getNodeType() const override;

  void setCueId(std::u32string_view);
  [[nodiscard]]std::u32string_view getCueId() const;
  void accept(ICueTreeVisitor &visitor) const override;
  void visit(const IdSelector &selector) override;
  void visit(const LanguageSelector &selector) override;
 private:
  std::u32string_view cueId;
};

} // namespace webvtt

#endif //LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_ROOT_OBJECT_HPP_
