#ifndef LIBWEBVTT_CLASS_OBJECT_H
#define LIBWEBVTT_CLASS_OBJECT_H

#include "elements/cue_node_objects/InternalNodeObject.h"

namespace WebVTT
{

    class ClassObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
         
    };
} // namespace WebVTT

#endif //LIBWEBVTT_CLASSOBJECT_H
