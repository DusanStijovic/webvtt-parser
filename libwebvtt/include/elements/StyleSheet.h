#ifndef WEBVTT_STYLE_SHEET_H
#define WEBVTT_STYLE_SHEET_H

#include "elements/Block.h"
#include "elements/style_objects/StyleSelector.h"
#include <memory>
#include <map>
#include <string>

namespace WebVTT
{

    class StyleSheet : public Block
    {
    public:
        void setSelector(const std::shared_ptr<StyleSelector> &newSelector);

    protected:
        std::map<std::string, std::string> cssRules;

    private:
        std::shared_ptr<StyleSelector> styleSelector;
    };

}

#endif //LIBWEBVTT_STYLE_SHEET_H
