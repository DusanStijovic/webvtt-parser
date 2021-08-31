#ifndef LIBWEBVTT_ITALIC_OBJECT_H
#define LIBWEBVTT_ITALIC_OBJECT_H

#include "elements/cue_nodes/InternalNodeObject.h"

namespace WebVTT
{
    class ItalicObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        void accept( ICueTreeVisitor &visitor) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_ITALICOBJECT_H
