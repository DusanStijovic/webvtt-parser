#ifndef WEBVTT_REGION_H
#define WEBVTT_REGION_H

#include <cstdint>
#include <tuple>
#include <string>
#include <memory>
#include <list>
#include "Block.h"

namespace WebVTT
{

    class Region : public Block
    {

    private:
        constexpr static uint32_t START_NUM_OF_LINES = 3;
        constexpr static double START_ANCHOR_POINT_X = 0;
        constexpr static double START_ANCHOR_POINT_Y = 100;
        std::u32string identifier;
        uint32_t width;
        uint32_t lines = START_NUM_OF_LINES;
        std::tuple<double, double> anchorPoint{START_ANCHOR_POINT_X, START_ANCHOR_POINT_Y};
        std::tuple<double, double> viewpointAnchorPoint{START_ANCHOR_POINT_X, START_ANCHOR_POINT_Y};
        uint32_t scrollValue;

    public:
        std::shared_ptr<Region>
        getRegionByIdentifier(const std::list<std::shared_ptr<Region>> &regions, std::u32string_view identifier);
    };
} //End of namespace

#endif //LIBWEBVTT_REGION_H
