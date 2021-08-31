#ifndef REGION_STYLE_SHEET_H
#define REGION_STYLE_SHEET_H
#include "StyleSheet.h"

namespace WebVTT
{
    class RegionStyleSheet : public StyleSheet
    {
    public:
        virtual StyleSheetType getStyleSheetType() override;
    };

} // namespace WebVTT

#endif //REGION_STYLE_SHEET_H