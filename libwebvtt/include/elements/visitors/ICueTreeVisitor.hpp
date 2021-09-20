#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_I_CUE_TREE_VISITOR_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_I_CUE_TREE_VISITOR_HPP_

#include "elements/cue_nodes/leaf_node_objects/TextObject.hpp"
#include "elements/cue_nodes/leaf_node_objects/TimeStampObject.hpp"

#include "elements/cue_nodes/internal_node_objects/BoldObject.hpp"
#include "elements/cue_nodes/internal_node_objects/ClassObject.hpp"
#include "elements/cue_nodes/internal_node_objects/ItalicObject.hpp"
#include "elements/cue_nodes/internal_node_objects/LanguageObject.hpp"
#include "elements/cue_nodes/internal_node_objects/RootObject.hpp"
#include "elements/cue_nodes/internal_node_objects/RubyObject.hpp"
#include "elements/cue_nodes/internal_node_objects/RubyTextObject.hpp"
#include "elements/cue_nodes/internal_node_objects/UnderlineObject.hpp"
#include "elements/cue_nodes/internal_node_objects/VoiceObject.hpp"

namespace webvtt {

class ICueTreeVisitor {
 public:
  // leaf node
  virtual void visit(const TimeStampObject &object) = 0;
  virtual void visit(const TextObject &object) = 0;

  //internal node
  virtual void visit(const BoldObject &object) = 0;
  virtual void visit(const ItalicObject &object) = 0;
  virtual void visit(const ClassObject &object) = 0;
  virtual void visit(const RubyObject &object) = 0;
  virtual void visit(const RubyTextObject &object) = 0;
  virtual void visit(const UnderlineObject &object) = 0;
  virtual void visit(const VoiceObject &object) = 0;
  virtual void visit(const LanguageObject &object) = 0;
  virtual void visit(const RootObject &object) = 0;

  virtual ~ICueTreeVisitor() = default;

};
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_I_CUE_TREE_VISITOR_HPP_
