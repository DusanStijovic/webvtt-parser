#ifndef LIBWEBVTT_TEXT_OBJECT_H
#define LIBWEBVTT_TEXT_OBJECT_H

#include "elements/cue_node_objects/LeafNodeObject.h"

namespace WebVTT
{
    class TextObject : public LeafNodeObject
    {
    public:
        TextObject(std::u32string_view input)
        {
        }
        virtual NodeObject::NodeType getNodeType() const;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_TEXT_OBJECT_H
