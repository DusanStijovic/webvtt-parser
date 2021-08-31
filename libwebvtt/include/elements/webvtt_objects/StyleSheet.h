#ifndef WEBVTT_STYLE_SHEET_H
#define WEBVTT_STYLE_SHEET_H

#include "Block.h"
#include "elements/style_selectors/StyleSelector.h"
#include <memory>
#include <map>
#include <string>
#include <list>

namespace WebVTT
{

    class StyleSheet : public Block
    {
    public:
        enum class StyleSheetType
        {
            UNDEFINED,
            CUE,
            REGION
        };

        void addSelector(std::unique_ptr<StyleSelector> &&newSelector);

        std::list<std::unique_ptr<StyleSelector>> &getSelectors();

        void addCSSRule(std::string name, std::string value);

        virtual StyleSheetType getStyleSheetType() = 0;
        static std::unique_ptr<StyleSheet> makeNewStyleSheet(StyleSheetType styleSheetType);

    protected:
        std::map<std::string, std::string> cssRules;

    private:
        std::list<std::unique_ptr<StyleSelector>> styleSelectors;
    };

}

#endif //LIBWEBVTT_STYLE_SHEET_H
