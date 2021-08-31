#ifndef LIBWEBVTT_VOICE_OBJECT_H
#define LIBWEBVTT_VOICE_OBJECT_H

#include "elements/cue_nodes/InternalNodeObject.h"

namespace WebVTT
{

    class VoiceObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        virtual void processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) override;
        void accept(ICueTreeVisitor &visitor) override;

    private:
        std::u32string name;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_VOICE_OBJECT_H
