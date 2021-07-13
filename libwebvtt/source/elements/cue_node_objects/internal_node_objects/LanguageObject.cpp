#include "elements/cue_node_objects/internal_node_objects/LanguageObject.h"
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
        if (nodeObejct->getNodeType() == value)
        {
            if (nodeObejct->getParent() != nullptr)
            {
                nodeObejct = nodeObejct->getParent();
            }
            else
            {
                //TODO Log error and continue
            }
        }
        else
        {
            //TODO Log error and continue
        }
    };

} // namespace WebVTT
