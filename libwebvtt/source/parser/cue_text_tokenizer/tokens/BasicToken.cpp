#include "parser/cue_text_tokenizer/tokens/BasicToken.hpp"
#include "elements/cue_nodes/leaf_node_objects/TextObject.hpp"
#include <memory>

namespace webvtt
{
    void BasicToken::process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language)
    {
        std::shared_ptr<TextObject> textObject = std::make_shared<TextObject>(tokenValue);
        nodeObject->appendChild(textObject);
        textObject->setParent(nodeObject);
    }

}
