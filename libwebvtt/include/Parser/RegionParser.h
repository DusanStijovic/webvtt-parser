#ifndef WEBVTT_CUE_PARSER_H
#define WEBVTT_CUE_PARSER_H

#include "Region.h"
#include <list>
#include <memory>

namespace WebVTT
{
    class RegionParser
    {
    private:
        std::list<std::shared_ptr<Region>> regions;
    };

} //End of namespace

#endif