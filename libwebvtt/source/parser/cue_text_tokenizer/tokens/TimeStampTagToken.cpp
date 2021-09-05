#include "parser/cue_text_tokenizer/tokens/TimeStampTagToken.hpp"
#include "parser/ParserUtil.hpp"
#include "elements/cue_nodes/NodeObject.hpp"
#include "elements/cue_nodes/leaf_node_objects/TimeStampObject.hpp"
#include "logger/LoggingUtility.hpp"
#include "exceptions/parser_util/ParsingTimeStampException.hpp"

namespace webvtt
{

    void TimeStampTagToken::process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language)
    {
        try
        {
            std::u32string_view input = this->tokenValue;
            auto position = input.begin();
            double time = ParserUtil::parseTimeStamp(input, position);

            if (position != input.end())
            {
                DILOGE("Timestamp contains extra characters" + utf8::utf32to8(input));
                return;
            }
            std::shared_ptr<TimeStampObject> timeStampObject = std::make_shared<TimeStampObject>(time);
            nodeObject->appendChild(timeStampObject);
            timeStampObject->setParent(nodeObject);
        }
        catch (const ParsingTimeStampException &error)
        {
            DILOGE(error.what());
            return;
        }
    }
}