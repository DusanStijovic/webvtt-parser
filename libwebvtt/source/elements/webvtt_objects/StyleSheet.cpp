#include "elements/webvtt_elements/StyleSheet.h"
#include "elements/webvtt_elements/CueStyleSheet.h"
#include "elements/webvtt_elements/RegionStyleSheet.h"

namespace WebVTT
{
    void StyleSheet::addSelector(std::unique_ptr<StyleSelector> &&newSelectorr)
    {
        this->styleSelectors.push_back(std::move(newSelectorr));
    }

    void StyleSheet::addCSSRule(std::string name, std::string value)
    {

        cssRules[name] = value;
    }

    std::list<std::unique_ptr<StyleSelector>> &StyleSheet::getSelectors()
    {
        return styleSelectors;
    }

    std::unique_ptr<StyleSheet> StyleSheet::makeNewStyleSheet(StyleSheetType styleSheetType)
    {
        switch (styleSheetType)
        {
        case StyleSheetType::CUE:
            return std::make_unique<CueStyleSheet>();
            break;
        case StyleSheetType::REGION:
            return std::make_unique<RegionStyleSheet>();
            break;
        default:
            return nullptr;
            break;
        }
    }
} // namespace WebVTT
