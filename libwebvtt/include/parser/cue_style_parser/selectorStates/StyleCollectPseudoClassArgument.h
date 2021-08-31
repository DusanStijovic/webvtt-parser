#ifndef STYLE_COLLECT_PSEUDO_ARGUMENT_H
#define STYLE_COLLECT_PSEUDO_ARGUMENT_H
#include "parser/cue_style_parser/states/StyleState.h"

namespace WebVTT
{
    class StyleCollectPseudoArgument : public StyleState
    {
    public:
        StyleCollectPseudoArgument() = default;
        void processState(StyleSheetParser &parser) override;
    };

} // namespace WebVTT

#endif // STYLE_COLLECT_PSEUDO_CLASS_ARGUMENT_H