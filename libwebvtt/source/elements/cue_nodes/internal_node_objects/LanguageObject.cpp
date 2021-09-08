#include "elements/cue_nodes/internal_node_objects/LanguageObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"

#include <stack>
#include <string>

namespace webvtt {
void LanguageObject::processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) {
  languages.push(annotation);
}

NodeObject::NodeType LanguageObject::getNodeType() const {
  return NodeObject::NodeType::LANGUAGE;
};

void LanguageObject::processEndToken(std::shared_ptr<NodeObject> &nodeObject,
                                     std::stack<std::u32string> &languages,
                                     NodeObject::NodeType value) {
  NodeObject::processEndToken(nodeObject, languages, value);
  if (nodeObject->getNodeType() == value) {
    if (!languages.empty())
      languages.pop();
  }
};

void
LanguageObject::accept(ICueTreeVisitor &visitor) const {
  visitor.visit(*this);
}
void LanguageObject::visit(const LanguageTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = true;
}
void LanguageObject::visit(const LanguageSelector &selector) {
  shouldApplyLastVisitedStyleSheet = selector.isValueMatch(this->language);
}

} // namespace webvtt
