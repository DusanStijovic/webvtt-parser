//
// Created by Dušan on 6/3/2021.
//

#include "elements/webvtt_elements/Region.h"
#include <algorithm>
#include <iterator>

namespace WebVTT
{

    Region *
    Region::getRegionByIdentifier(const std::list<std::unique_ptr<Region>> &regions, std::u32string_view identifier)
    {

        auto found = std::find_if(regions.rbegin(), regions.rend(), [&identifier](const std::unique_ptr<Region> &region)
                                  { return region->identifier == identifier; });
        if (found == regions.rend())
            return nullptr;
        else
            return found->get();
    }

    void Region::setId(std::u32string_view newIdentifier)
    {
        this->identifier = std::u32string(newIdentifier);
    }

    void Region::setWidth(double newWidth)
    {
        this->width = newWidth;
    }

    void Region::setLines(int newNumOfLines)
    {
        this->lines = newNumOfLines;
    }

    void Region::setViewAnchorPort(std::tuple<double, double> newViewPortAnchor)
    {
        this->viewPortAnchor = newViewPortAnchor;
    }

    void Region::setAnchor(std::tuple<double, double> newAnchor)
    {
        this->anchor = newAnchor;
    }

    void Region::setScrollValue(ScrollType newScrollValue)
    {
        this->scrollValue = newScrollValue;
    }

}
