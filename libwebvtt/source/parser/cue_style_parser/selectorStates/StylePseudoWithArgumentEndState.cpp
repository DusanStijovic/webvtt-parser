#include "parser/cue_style_parser/selectorStates/StylePseudoWithArgumentEndState.h"
#include "parser/StyleSheetParser.h"

namespace WebVTT
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
} // namespace WebVTT
