#ifndef STYLE_SHEET_PARSER_H
#define STYLE_SHEET_PARSER_H

#include "StyleSheet.h"
#include <list>
#include <memory>

namespace WebVTT
{
    class StyleSheetParser
    {
    private:
        std::list<std::shared_ptr<StyleSheet>> styleSheets;
    };
}

#endif