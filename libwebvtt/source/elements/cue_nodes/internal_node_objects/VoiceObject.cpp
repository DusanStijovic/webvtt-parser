#include "elements/cue_nodes/internal_node_objects/VoiceObject.h"
#include "elements/visitors/ICueTreeVisitor.h"

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

    void
    VoiceObject::accept(ICueTreeVisitor &visitor)
    {
        visitor.visitOnEntry(*this);
        visitChildren(visitor);
        visitor.visitOnExit(*this);
    }

} // namespace WebVTT
