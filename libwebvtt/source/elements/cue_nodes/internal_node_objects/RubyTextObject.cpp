#include "elements/cue_nodes/internal_node_objects/RubyTextObject.hpp"
#include "elements/visitors/ICueTreeVisitor.hpp"
#include "logger/LoggingUtility.hpp"

namespace webvtt {
NodeObject::NodeType RubyTextObject::getNodeType() const {
  return NodeObject::NodeType::RUBY_TEXT;
};
void RubyTextObject::processEndToken(std::shared_ptr<NodeObject> &nodeObject,
                                     std::stack<std::u32string> &languages,
                                     NodeType value) {
  NodeObject::processEndToken(nodeObject, languages, value);

  if (value == NodeObject::NodeType::RUBY && nodeObject->getNodeType() == NodeObject::NodeType::RUBY_TEXT) {
    auto parent = nodeObject->getParent().lock();
    if (parent == nullptr) {
      DILOGE("No parent to ruby text object");
      return;
    }
    auto grandparent = parent->getParent().lock();
    if (grandparent == nullptr) {
      DILOGE("No grand parent to ruby text object");
      return;
    }
    nodeObject = grandparent;
    return;
  }
};

void RubyTextObject::accept(ICueTreeVisitor &visitor) const  {
  visitor.visit(*this);
}

} // namespace webvtt
