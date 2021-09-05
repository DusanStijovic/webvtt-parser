#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_LANGUAGE_OBJECT_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_LANGUAGE_OBJECT_HPP_

#include "elements/cue_nodes/InternalNodeObject.hpp"

namespace webvtt {

class LanguageObject : public InternalNodeObject {
 public:
  virtual NodeType getNodeType() const override;
  virtual void processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) override;
  virtual void processEndToken(std::shared_ptr<NodeObject> &nodeObject,
                               std::stack<std::u32string> &languages,
                               NodeType value) override;
  void accept(ICueTreeVisitor &visitor) const  override;

 private:
};
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_CUE_NODES_INTERNAL_NODE_OBJECTS_LANGUAGE_OBJECT_HPP_
