#ifndef LIBWEBVTT_ROOT_OBJECT_H
#define LIBWEBVTT_ROOT_OBJECT_H

#include "elements/cue_node_objects/InternalNodeObject.h"

namespace WebVTT
{
    class RootObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
       
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ROOT_OBJECT_H
