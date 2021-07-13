#include "parser/cue_text_tokenizer/tokens/TimeStampTagToken.h"
#include "parser/ParserUtil.h"
#include "elements/cue_node_objects/NodeObject.h"
#include "elements/cue_node_objects/leaf_node_objects/TimeStampObject.h"

namespace WebVTT
{

    void TimeStampTagToken::process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language)
    {
        std::u32string_view input = this->tokenValue;
        auto position = input.begin();
        auto timeOptional = ParserUtil::parseTimeStamp(input, position);
        if (!timeOptional.has_value())
        {
            //TODO Log error
            return;
        }
        double time = timeOptional.value();
        if (position != input.end())
        {
            //TODO Log error
            return;
        }
        std::shared_ptr<TimeStampObject> timeStampObject = std::make_shared<TimeStampObject>(time);
        nodeObject->appendChild(timeStampObject);
        timeStampObject->setParent(nodeObject);
    }
}