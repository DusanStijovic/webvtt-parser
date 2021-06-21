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

    public:
        enum Scroll
        {
            NONE,
            UP
        };

        std::shared_ptr<Region>
        getRegionByIdentifier(const std::list<std::shared_ptr<Region>> &regions, std::u32string_view identifier);

        void setId(std::u32string_view identifier)
        {
            this->identifier = {identifier.data(), identifier.size()};
        }

        void setWidth(double width)
        {
            this->width = width;
        }

        void setLines(int numOfLines)
        {
            this->lines = 3;
        }

        void setViewAnchorPort(std::tuple<double, double> viewPortAnchor)
        {
            this->viewPortAnchor = viewPortAnchor;
        }

        void setAnchor(std::tuple<double, double> anchor)
        {
            this->anchor = anchor;
        }

        void setScrollValue(Scroll scrollValue)
        {
            this->scrollValue = scrollValue;
        }

    private:
        constexpr static double DEFAULT_WIDTH = 100;
        constexpr static uint32_t DEFAULT_NUM_OF_LINES = 3;
        constexpr static double DEFAULT_ANCHOR_PORT_X = 0;
        constexpr static double DEFAULT_ANCHOR_PORT_Y = 100;
        std::u32string identifier;
        uint32_t width = DEFAULT_WIDTH;
        uint32_t lines = DEFAULT_NUM_OF_LINES;
        std::tuple<double, double> anchor{DEFAULT_ANCHOR_PORT_X, DEFAULT_ANCHOR_PORT_Y};
        std::tuple<double, double> viewPortAnchor{DEFAULT_ANCHOR_PORT_X, DEFAULT_ANCHOR_PORT_Y};
        Scroll scrollValue = NONE;
    };

} //End of namespace

#endif //LIBWEBVTT_REGION_H
