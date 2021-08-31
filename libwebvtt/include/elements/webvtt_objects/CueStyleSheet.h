#ifndef CUE_STYLE_SHEET_H
#define CUE_STYLE_SHEET_H
#include "StyleSheet.h"

namespace WebVTT
{
    class CueStyleSheet : public StyleSheet
    {
    public:
        virtual StyleSheetType getStyleSheetType() override;
    };

} // namespace WebVTT

#endif //CUE_STYLE_SHEET_H