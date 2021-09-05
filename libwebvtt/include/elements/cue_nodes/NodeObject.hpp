#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_NODE_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_NODE_OBJECT_HPP_

#include <list>
#include <stack>
#include <memory>

namespace webvtt {

class Cue;
class ICueTreeVisitor;

class NodeObject {
 public:

  NodeObject() = default;
  NodeObject(const NodeObject &) = delete;
  NodeObject(NodeObject &&) = delete;
  NodeObject &operator=(const NodeObject &) = delete;
  NodeObject &operator=(NodeObject &&) = delete;
  virtual ~NodeObject() = default;

  enum class NodeType {
    //Internal NodeTypes
    UNDEFINED,
    ROOT,
    BOLD,
    CLASS,
    ITALIC,
    LANGUAGE,
    RUBY,
    RUBY_TEXT,
    UNDERLINE,
    VOICE,
    //Leaf Nodes Types
    TEXT,
    TIME_STAMP
  };
  virtual void appendChild(std::shared_ptr<NodeObject> nodeObject) = 0;

  virtual void setParent(const std::weak_ptr<NodeObject> &newParent);
  virtual std::weak_ptr<NodeObject> getParent();

  [[nodiscard]] virtual NodeType getNodeType() const = 0;

  virtual void processEndToken(std::shared_ptr<NodeObject> &nodeObject,
                               std::stack<std::u32string> &languages,
                               NodeType value);

  virtual void accept(ICueTreeVisitor &visitor) const = 0;
  virtual void visitChildren(ICueTreeVisitor &visitor) = 0;

 protected:
  std::weak_ptr<NodeObject> parent;

};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_NODE_OBJECT_HPP_
