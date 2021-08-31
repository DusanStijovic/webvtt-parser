#ifndef LIBWEBVTT_RUBY_TEXT_OBJECT_H
#define LIBWEBVTT_RUBY_TEXT_OBJECT_H

#include "elements/cue_nodes/InternalNodeObject.h"

namespace WebVTT
{

    class RubyTextObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        virtual void processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages, NodeObject::NodeType value) override;
        void accept(ICueTreeVisitor &visitor) override;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_RUBY_TEXT_OBJECT_H
