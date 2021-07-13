#ifndef LIBWEBVTT_TIME_STAMP_OBJECT_H
#define LIBWEBVTT_TIME_STAMP_OBJECT_H

#include "elements/cue_node_objects/LeafNodeObject.h"

namespace WebVTT
{
    class TimeStampObject : public LeafNodeObject
    {
    public:
        TimeStampObject(double newTime) : time(newTime) {}

        virtual NodeObject::NodeType getNodeType() const;

    private:
        double time;
    };

} // namespace WebVTT

#endif
