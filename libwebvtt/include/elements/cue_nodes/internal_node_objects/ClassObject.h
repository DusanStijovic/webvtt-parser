#ifndef LIBWEBVTT_CLASS_OBJECT_H
#define LIBWEBVTT_CLASS_OBJECT_H

#include "elements/cue_nodes/InternalNodeObject.h"

namespace WebVTT
{

    class ClassObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        void accept( ICueTreeVisitor &visitor) override;
    };
} // namespace WebVTT

#endif //LIBWEBVTT_CLASSOBJECT_H
