#include "parser/cue_text_tokenizer/tokens/EndTagToken.hpp"
#include "elements/cue_nodes/InternalNodeObject.hpp"
namespace webvtt
{

    void EndTagToken::process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages)
    {
        NodeObject::NodeType nodeType = InternalNodeObject::convertToInternalNodeType(this->tokenValue);
        nodeObject->processEndToken(nodeObject, languages, nodeType);
    }
}