#ifndef LIBWEBVTT_ROOT_OBJECT_H
#define LIBWEBVTT_ROOT_OBJECT_H

#include "elements/cue_nodes/InternalNodeObject.h"

namespace WebVTT
{
    class RootObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        void accept(ICueTreeVisitor &visitor) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ROOT_OBJECT_H
