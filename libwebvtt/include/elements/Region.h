#ifndef WEBVTT_REGION_H
#define WEBVTT_REGION_H

#include <cstdint>
#include <tuple>
#include <string>
#include <memory>
#include <list>
#include "Block.h"

namespace WebVTT {


    /**
     * Class representing region in WebVTT. It containt region id and region settings
     */
    class Region : public Block {

    public:
        enum ScrollType {
            NONE,
            UP
        };

        /**
         *
         * @param regions list of regions that will be searched
         * @param identifier id of region that has been asked for
         * @return region with given id from list of given regions, otherwise nullptr
         */
        static std::shared_ptr<Region>
        getRegionByIdentifier(const std::list<std::shared_ptr<Region>> &regions, std::u32string_view identifier);

        /**
         * Set region identifier
         * @param newIdentifier new region identifier
         */
        void setId(std::u32string_view newIdentifier);

        /**
         * Set region width
         *
         * @param newWidth new region width
         */
        void setWidth(double newWidth);

        /**
         * Set region number of lined
         *
         * @param newNumOfLines new number of lines for region
         */
        void setLines(int newNumOfLines);

        /**
         * Set x and y coordinates of view port anchor's
         * @param viewPortAnchor new x and y coordinates of view port anchor's
         */
        void setViewAnchorPort(std::tuple<double, double> newViewPortAnchor);

        /**
         * Set x and y coordinates of region anchor's
         * @param newAnchor new x and y  coordinates of region anchor's
         */
        void setAnchor(std::tuple<double, double> newAnchor);

        /**
         * Set new scroll value
         * @param newScrollValue new scroll value, one instance of ScrollType
         */
        void setScrollValue(ScrollType newScrollValue);

    private:
        /**
         * Constexpresions for region settings default values
         */
        constexpr static double DEFAULT_WIDTH = 100;
        constexpr static uint32_t DEFAULT_NUM_OF_LINES = 3;
        constexpr static double DEFAULT_ANCHOR_PORT_X = 0;
        constexpr static double DEFAULT_ANCHOR_PORT_Y = 100;

        std::u32string identifier;
        uint32_t width = DEFAULT_WIDTH;
        uint32_t lines = DEFAULT_NUM_OF_LINES;
        std::tuple<double, double> anchor{DEFAULT_ANCHOR_PORT_X, DEFAULT_ANCHOR_PORT_Y};
        std::tuple<double, double> viewPortAnchor{DEFAULT_ANCHOR_PORT_X, DEFAULT_ANCHOR_PORT_Y};
        ScrollType scrollValue = NONE;
    };

} //End of namespace

#endif