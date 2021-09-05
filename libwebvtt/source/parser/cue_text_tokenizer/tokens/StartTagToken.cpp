#include "parser/cue_text_tokenizer/tokens/StartTagToken.hpp"
#include "elements/cue_nodes/InternalNodeObject.hpp"
#include "logger/LoggingUtility.hpp"

namespace webvtt
{

    void StartTagToken::process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages)
    {

        NodeObject::NodeType type = InternalNodeObject::convertToInternalNodeType(tokenValue);
        if (type == NodeObject::NodeType::UNDEFINED)
            return;

        if (type == NodeObject::NodeType::RUBY_TEXT &&
            nodeObject->getNodeType() != NodeObject::NodeType::RUBY)
            return;
        std::shared_ptr<InternalNodeObject> newObject = InternalNodeObject::makeInternalNode(type);

        newObject->setClasses(this->classes);
        newObject->processAnnotationString(languages, this->annotations);

        if (!languages.empty())
            newObject->setLanguage(languages.top());

        newObject->setParent(nodeObject);
        nodeObject->appendChild(newObject);
        nodeObject = newObject;
    }
}