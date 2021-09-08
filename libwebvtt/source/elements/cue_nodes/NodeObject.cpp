#include "elements/cue_nodes/NodeObject.hpp"
#include "exceptions/NotImplementedError.hpp"
#include "logger/LoggingUtility.hpp"

namespace webvtt {
void NodeObject::setParent(const std::weak_ptr<NodeObject> &newParent) {
  this->parent = newParent;
};

std::weak_ptr<NodeObject> NodeObject::getParent() {
  return this->parent;
}

void NodeObject::processEndToken(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages,
                                 NodeType value) {
  if (nodeObject->getNodeType() == value) {
    auto temp = nodeObject->getParent().lock();
    if (temp != nullptr)
      nodeObject = temp;
  } else {
    DILOGE("Start tag voiceName and end tag voiceName is not same");
  }
}
void NodeObject::visit(const MatchAllSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const IdSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const ClassSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}

void NodeObject::visit(const ItalicTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const LanguageTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const UnderlineTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const VoiceTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const VoiceSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const ClassTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const BoldTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const RubyTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const RubyTextTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void NodeObject::visit(const LanguageSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}

void NodeObject::visit(const CompoundSelector &selector) {
  throw NotImplementedError();
}
void NodeObject::visit(const CombinatorSelector &selector) {
  throw NotImplementedError();
}
bool NodeObject::IsShouldApplyLastVisitedStyleSheet() const {
  return shouldApplyLastVisitedStyleSheet;
}

} //Enf of namespace