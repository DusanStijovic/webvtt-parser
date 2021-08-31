#ifndef LIBWEBVTT_UNDERLINE_OBJECT_H
#define LIBWEBVTT_UNDERLINE_OBJECT_H

#include "elements/cue_nodes/InternalNodeObject.h"

namespace WebVTT
{
    class UnderlineObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        void accept(ICueTreeVisitor &visitor) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_UNDERLINE_OBJECT_H
