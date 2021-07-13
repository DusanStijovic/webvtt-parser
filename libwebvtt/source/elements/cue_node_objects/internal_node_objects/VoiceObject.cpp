#include "elements/cue_node_objects/internal_node_objects/VoiceObject.h"

namespace WebVTT
{

    void VoiceObject::processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation)
    {
        this->name = annotation;
    }
     NodeObject::NodeType VoiceObject::getNodeType() const
    {
        return NodeObject::NodeType::VOICE;
    };


} // namespace WebVTT
