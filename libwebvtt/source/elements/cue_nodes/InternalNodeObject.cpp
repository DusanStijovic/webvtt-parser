#include "elements/cue_nodes/InternalNodeObject.hpp"

#include "elements/cue_nodes/internal_node_objects/BoldObject.hpp"
#include "elements/cue_nodes/internal_node_objects/ClassObject.hpp"
#include "elements/cue_nodes/internal_node_objects/ItalicObject.hpp"
#include "elements/cue_nodes/internal_node_objects/LanguageObject.hpp"
#include "elements/cue_nodes/internal_node_objects/RubyObject.hpp"
#include "elements/cue_nodes/internal_node_objects/RubyTextObject.hpp"
#include "elements/cue_nodes/internal_node_objects/UnderlineObject.hpp"
#include "elements/cue_nodes/internal_node_objects/VoiceObject.hpp"

#include <stack>
#include <string>

namespace webvtt {
void InternalNodeObject::appendChild(std::shared_ptr<NodeObject> nodeObject) {
  children.push_back(nodeObject);
}

NodeObject::NodeType
InternalNodeObject::convertToInternalNodeType(std::u32string_view nodeTypeName) {
  if (nodeTypeName == U"b")
    return NodeType::BOLD;
  if (nodeTypeName == U"c")
    return NodeType::CLASS;
  if (nodeTypeName == U"i")
    return NodeType::ITALIC;
  if (nodeTypeName == U"lang")
    return NodeType::LANGUAGE;
  if (nodeTypeName == U"ruby")
    return NodeType::RUBY;
  if (nodeTypeName == U"u")
    return NodeType::UNDERLINE;
  if (nodeTypeName == U"v")
    return NodeType::VOICE;
  if (nodeTypeName == U"rt")
    return NodeType::RUBY_TEXT;
  return NodeType::UNDEFINED;
};

std::shared_ptr<InternalNodeObject> InternalNodeObject::makeInternalNode(NodeObject::NodeType nodeType) {
  std::shared_ptr<InternalNodeObject> retValue = nullptr;
  switch (nodeType) {
    case NodeType::BOLD:retValue = std::make_shared<BoldObject>();
      break;
    case NodeType::CLASS:retValue = std::make_shared<ClassObject>();
      break;
    case NodeType::ITALIC:retValue = std::make_shared<ItalicObject>();
      break;
    case NodeType::LANGUAGE:retValue = std::make_shared<LanguageObject>();
      break;
    case NodeType::RUBY:retValue = std::make_shared<RubyObject>();
      break;
    case NodeType::RUBY_TEXT:retValue = std::make_shared<RubyTextObject>();
      break;
    case NodeType::UNDERLINE:retValue = std::make_shared<UnderlineObject>();
      break;
    case NodeType::VOICE:return std::make_shared<VoiceObject>();
      break;
    default:retValue = nullptr;
      break;
  }
  return retValue;
};

void InternalNodeObject::setClasses(std::list<std::u32string> &newClasses) {
  this->classes = newClasses;
}
void InternalNodeObject::setLanguage(std::u32string &newLanguage) {
  this->language = newLanguage;
};
void InternalNodeObject::processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) {
  //Do nothing by default
}

void InternalNodeObject::visitChildren(ICueTreeVisitor &visitor) {
  for (auto &child : children)
    child->accept(visitor);
}
const std::list<std::u32string> &InternalNodeObject::getClasses() {
  return classes;
}

std::u32string_view InternalNodeObject::getLanguage() {
  return language;
}

} // namespace webvtt
