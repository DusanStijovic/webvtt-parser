#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_ICUE_TREE_VISITOR_H_
#define LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_ICUE_TREE_VISITOR_H_

#include "elements/cue_nodes/leaf_node_objects/TextObject.h"
#include "elements/cue_nodes/leaf_node_objects/TimeStampObject.h"

#include "elements/cue_nodes/internal_node_objects/BoldObject.h"
#include "elements/cue_nodes/internal_node_objects/ClassObject.h"
#include "elements/cue_nodes/internal_node_objects/ItalicObject.h"
#include "elements/cue_nodes/internal_node_objects/LanguageObject.h"
#include "elements/cue_nodes/internal_node_objects/RootObject.h"
#include "elements/cue_nodes/internal_node_objects/RubyObject.h"
#include "elements/cue_nodes/internal_node_objects/RubyTextObject.h"
#include "elements/cue_nodes/internal_node_objects/UnderlineObject.h"
#include "elements/cue_nodes/internal_node_objects/VoiceObject.h"

namespace WebVTT
{

    class ICueTreeVisitor
    {
    public:
        // leaf node
        virtual void visitOnEntry(const TimeStampObject &object) = 0;
        virtual void visitOnEntry(const TextObject &object) = 0;

        //internal node
        virtual void visitOnEntry(const BoldObject &object) = 0;
        virtual void visitOnEntry(const ItalicObject &object) = 0;
        virtual void visitOnEntry(const ClassObject &object) = 0;
        virtual void visitOnEntry(const RubyObject &object) = 0;
        virtual void visitOnEntry(const RubyTextObject &object) = 0;
        virtual void visitOnEntry(const UnderlineObject &object) = 0;
        virtual void visitOnEntry(const VoiceObject &object) = 0;
        virtual void visitOnEntry(const LanguageObject &object) = 0;
        virtual void visitOnEntry(const RootObject &object) = 0;

        // leaf node
        virtual void visitOnExit(const TimeStampObject &object) = 0;
        virtual void visitOnExit(const TextObject &object) = 0;

        //internal node
        virtual void visitOnExit(const BoldObject &object) = 0;
        virtual void visitOnExit(const ItalicObject &object) = 0;
        virtual void visitOnExit(const ClassObject &object) = 0;
        virtual void visitOnExit(const RubyObject &object) = 0;
        virtual void visitOnExit(const RubyTextObject &object) = 0;
        virtual void visitOnExit(const UnderlineObject &object) = 0;
        virtual void visitOnExit(const VoiceObject &object) = 0;
        virtual void visitOnExit(const LanguageObject &object) = 0;
        virtual void visitOnExit(const RootObject &object) = 0;
    };
} // namespace WebVTT

#endif //LIBWEBVTT_INCLUDE_ELEMENTS_VISITORS_ICUETREEVISITOR_H_
