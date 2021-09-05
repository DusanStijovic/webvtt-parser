#include "parser/cue_style_parser/selectorStates/StylePseudoWithArgumentEndState.hpp"
#include "parser/object_parser/StyleSheetParser.hpp"

namespace webvtt
{

    void
    StylePseudoWithArgumentEndState::preprocessBuffer(StyleSheetParser &parser)
    {
        if (parser.getBuffer().empty() || parser.getAdditionalBuffer().empty())
            parser.setState(StyleState::StyleStateType::ERROR);
    }

    std::unique_ptr<StyleSelector> StylePseudoWithArgumentEndState::makeNewStyleSelector(StyleSheetParser &parser)
    {
        auto help = makeNewPseudoStyleSelector(parser);
        parser.getBuffer().clear();
        parser.getAdditionalBuffer().clear();
        return help;
    }
} // namespace webvtt
