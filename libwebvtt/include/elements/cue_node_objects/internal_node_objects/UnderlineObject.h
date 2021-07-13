#ifndef LIBWEBVTT_UNDERLINE_OBJECT_H
#define LIBWEBVTT_UNDERLINE_OBJECT_H

#include "elements/cue_node_objects/InternalNodeObject.h"

namespace WebVTT
{
    class UnderlineObject: public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
   
    };

} // namespace WebVTT

#endif //LIBWEBVTT_UNDERLINE_OBJECT_H
