#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_UNDERLINE_VOICE_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_UNDERLINE_VOICE_OBJECT_HPP_

#include "elements/cue_nodes/InternalNodeObject.hpp"

namespace webvtt {

class VoiceObject : public InternalNodeObject {
 public:
  [[nodiscard]] NodeType getNodeType() const override;
  void processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) override;
  void accept(ICueTreeVisitor &visitor) const override;
  void visit(const VoiceTypeSelector &selector) override;
  void visit(const VoiceSelector &selector) override;
 private:
  std::u32string voiceName;
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_UNDERLINE_VOICE_OBJECT_HPP_
