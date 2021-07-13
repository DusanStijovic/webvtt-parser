#ifndef LIBWEBVTT_RUBY_OBJECT_H
#define LIBWEBVTT_RUBY_OBJECT_H

#include "elements/cue_node_objects/InternalNodeObject.h"

namespace WebVTT
{

  class RubyObject : public InternalNodeObject
  {
  public:
    virtual NodeType getNodeType() const override;
    
  };

} // namespace WebVTT

#endif //LIBWEBVTT_RUBY_OBJECT_H
