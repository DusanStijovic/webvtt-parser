#include "parser/cue_text_tokenizer/tokens/EndTagToken.h"
#include "elements/cue_node_objects/InternalNodeObject.h"
namespace WebVTT
{

    void EndTagToken::process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &languages)
    {
        NodeObject::NodeType nodeType = InternalNodeObject::convertToInternalNodeType(this->tokenValue);
        nodeObject->processEndToken(nodeObject, languages, nodeType);
    }
}