#include "elements/cue_nodes/internal_node_objects/VoiceObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

namespace webvtt {

void VoiceObject::processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) {
  this->voiceName = annotation;
}
NodeObject::NodeType VoiceObject::getNodeType() const {
  return NodeObject::NodeType::VOICE;
};

void
VoiceObject::accept(ICueTreeVisitor &visitor) const {
  visitor.visit(*this);
}
void VoiceObject::visit(const VoiceTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = true;
}
void VoiceObject::visit(const VoiceSelector &selector) {
  shouldApplyLastVisitedStyleSheet = selector.isValueMatch(this->voiceName);
}

} // namespace webvtt
