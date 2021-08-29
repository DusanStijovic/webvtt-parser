#ifndef LIBWEBVTT_LANGUAGE_OBJECT_H
#define LIBWEBVTT_LANGUAGE_OBJECT_H

#include "elements/cue_node_objects/InternalNodeObject.h"

namespace WebVTT
{

    class LanguageObject : public InternalNodeObject
    {
    public:
        virtual NodeType getNodeType() const override;
        virtual void processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation) override;
        virtual void processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages, NodeType value) override;

    private:
      
    };
} // namespace WebVTT

#endif //LIBWEBVTT_LANGUAGEOBJECT_H
