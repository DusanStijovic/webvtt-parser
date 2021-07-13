#ifndef LIBWEBVTT_NODE_OBJECT_H
#define LIBWEBVTT_NODE_OBJECT_H

#include <list>
#include <stack>
#include <memory>

namespace WebVTT
{

    class NodeObject
    {
    public:
        enum class NodeType
        {
            //Internal NodeTypes
            UNDEFINED,
            ROOT,
            BOLD,
            CLASS,
            ITALIC,
            LANGUAGE,
            RUBY,
            RUBY_TEXT,
            UNDERLINE,
            VOICE,
            //Leaf Nodes Types
            TEXT,
            TIME_STAMP
        };
        virtual void appendChild(std::shared_ptr<NodeObject> nodeObject) = 0;

        virtual void setParent(const std::shared_ptr<NodeObject> &newParent);
        virtual std::shared_ptr<NodeObject> getParent();

        virtual NodeType getNodeType() const = 0;

        virtual void processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages, NodeType value);

        virtual ~NodeObject() = default;

    private:
        std::shared_ptr<NodeObject> parent = nullptr;
    };

} // namespace WebVTT

#endif //LIBWEBVTT_NODEOBJECT_H
