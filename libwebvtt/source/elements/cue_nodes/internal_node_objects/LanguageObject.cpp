#include "elements/cue_nodes/internal_node_objects/LanguageObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

#include <stack>
#include <string>

namespace WebVTT
{
    void LanguageObject::processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation)
    {
        languages.push(annotation);
    }

    NodeObject::NodeType LanguageObject::getNodeType() const
    {
        return NodeObject::NodeType::LANGUAGE;
    };

    void LanguageObject::processEndToken(std::shared_ptr<NodeObject> &nodeObejct, std::stack<std::u32string> &languages, NodeObject::NodeType value)
    {
        NodeObject::processEndToken(nodeObejct, languages, value);
        if (nodeObejct->getNodeType() == value)
        {
            if (!languages.empty())
                languages.pop();
        }
    };

  
    void
    LanguageObject ::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
