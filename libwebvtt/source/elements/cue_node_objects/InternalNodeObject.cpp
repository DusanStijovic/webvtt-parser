#include "elements/cue_node_objects/InternalNodeObject.h"

#include "elements/cue_node_objects/internal_node_objects/BoldObject.h"
#include "elements/cue_node_objects/internal_node_objects/ClassObject.h"
#include "elements/cue_node_objects/internal_node_objects/ItalicObject.h"
#include "elements/cue_node_objects/internal_node_objects/LanguageObject.h"
#include "elements/cue_node_objects/internal_node_objects/RubyObject.h"
#include "elements/cue_node_objects/internal_node_objects/RubyTextObject.h"
#include "elements/cue_node_objects/internal_node_objects/UnderlineObject.h"
#include "elements/cue_node_objects/internal_node_objects/VoiceObject.h"

#include <stack>
#include <string>

namespace WebVTT
{
    void InternalNodeObject::appendChild(std::shared_ptr<NodeObject> nodeObject)
    {
        listOfObject.push_back(nodeObject);
    }

    NodeObject::NodeType
    InternalNodeObject::convertToInternalNodeType(std::u32string_view nodeTypeName)
    {
        if (nodeTypeName == U"b")
            return NodeType::BOLD;
        if (nodeTypeName == U"c")
            return NodeType::CLASS;
        if (nodeTypeName == U"i")
            return NodeType::ITALIC;
        if (nodeTypeName == U"lang")
            return NodeType::LANGUAGE;
        if (nodeTypeName == U"ruby")
            return NodeType::RUBY;
        if (nodeTypeName == U"u")
            return NodeType::UNDERLINE;
        if (nodeTypeName == U"v")
            return NodeType::VOICE;
        if (nodeTypeName == U"rt")
            return NodeType::RUBY_TEXT;
        return NodeType::UNDEFINED;
    };

    std::shared_ptr<InternalNodeObject> InternalNodeObject::makeInternalNode(NodeObject::NodeType nodeType)
    {
        std::shared_ptr<InternalNodeObject> retValue = nullptr;
        switch (nodeType)
        {
        case NodeType::BOLD:
            retValue = std::make_shared<BoldObject>();
            break;
        case NodeType::CLASS:
            retValue = std::make_shared<ClassObject>();
            break;
        case NodeType::ITALIC:
            retValue = std::make_shared<ItalicObject>();
            break;
        case NodeType::LANGUAGE:
            retValue = std::make_shared<LanguageObject>();
            break;
        case NodeType::RUBY:
            retValue = std::make_shared<RubyObject>();
            break;
        case NodeType::RUBY_TEXT:
            retValue = std::make_shared<RubyTextObject>();
            break;
        case NodeType::UNDERLINE:
            retValue = std::make_shared<UnderlineObject>();
            break;
        case NodeType::VOICE:
            return std::make_shared<VoiceObject>();
            break;
        case NodeType::UNDEFINED:
        case NodeType::TEXT:
        case NodeType::TIME_STAMP:
            retValue = nullptr;
            break;
        }
        return retValue;
    };

    void InternalNodeObject::setClasses(std::list<std::u32string> &newClasses)
    {
        this->classes = newClasses;
    }
    void InternalNodeObject::setLanguage(std::u32string &languages)
    {
        this->language = language;
    };
    void InternalNodeObject::processAnnotationString(std::stack<std::u32string> &languages, std::u32string &annotation)
    {
        //Do nothing by default
    }
} // namespace WebVTT
