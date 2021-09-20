#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECT_HPP_

#include "NodeObject.hpp"
#include <string>
#include <stack>

namespace webvtt {
class InternalNodeObject : public NodeObject {

 public:
  InternalNodeObject() = default;

  void setClasses(std::list<std::u32string> &newClasses);
  const std::list<std::u32string> &getClasses();

  virtual void setLanguage(std::u32string &languages);
  std::u32string_view getLanguage();

  virtual void processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation);

  static NodeType
  convertToInternalNodeType(std::u32string_view nodeTypeName);
  static std::shared_ptr<InternalNodeObject> makeInternalNode(NodeType nodeType);

  void appendChild(std::shared_ptr<NodeObject> nodeObject) override;
  void visitChildren(ICueTreeVisitor &visitor) override;

  void visit(const ClassSelector &selector) override;




 protected:
  std::list<std::shared_ptr<NodeObject>> children;
  std::list<std::u32string> classes;
  std::u32string language;

};
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECT_HPP_
