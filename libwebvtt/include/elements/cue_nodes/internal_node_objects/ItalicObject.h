#ifndef LIBWEBVTT_ITALIC_OBJECT_H
#define LIBWEBVTT_ITALIC_OBJECT_H

#include "elements/cue_node_objects/InternalNodeObject.h"

namespace WebVTT
{
    class ItalicObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
      
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ITALICOBJECT_H
