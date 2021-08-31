#ifndef LIBWEBVTT_INTERNAL_NODE_OBJECT_H
#define LIBWEBVTT_INTERNAL_NODE_OBJECT_H

#include "NodeObject.h"
#include <string>
#include <stack>

namespace WebVTT
{
    class InternalNodeObject : public NodeObject
    {

    public:
        InternalNodeObject() = default;

        void setClasses(std::list<std::u32string> &newClasses);
        virtual void setLanguage(std::u32string &languages);
        virtual void processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation);

        static NodeType
        convertToInternalNodeType(std::u32string_view nodeTypeName);
        static std::shared_ptr<InternalNodeObject> makeInternalNode(NodeType nodeType);

        void appendChild(std::shared_ptr<NodeObject> nodeObject);

    protected:
        std::list<std::shared_ptr<NodeObject>> children;
        std::list<std::u32string> classes;
        std::u32string language;

        void visitChildren(ICueTreeVisitor &visitor) override;
    };
}

#endif
