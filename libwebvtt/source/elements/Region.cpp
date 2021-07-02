//
// Created by Dušan on 6/3/2021.
//

#include "elements/Region.h"
#include <algorithm>
#include <iterator>




namespace WebVTT {

    std::shared_ptr<Region>
    Region::getRegionByIdentifier(const std::list<std::shared_ptr<Region>> &regions, std::u32string_view identifier) {
        auto begin = std::make_reverse_iterator(regions.begin());
        auto end = std::make_reverse_iterator(regions.end());
        auto found = std::find_if(begin, end, [&identifier](const std::shared_ptr<Region> &region) {
            return region->identifier == identifier;
        });
        if (found == end)
            return nullptr;
        else
            return *found;
    }

    void Region::setId(std::u32string_view newIdentifier) {
        this->identifier = std::u32string(newIdentifier);
    }

    void Region::setWidth(double newWidth) {
        this->width = newWidth;
    }

    void Region::setLines(int newNumOfLines) {
        this->lines = newNumOfLines;
    }

    void Region::setViewAnchorPort(std::tuple<double, double> newViewPortAnchor) {
        this->viewPortAnchor = newViewPortAnchor;
    }

    void Region::setAnchor(std::tuple<double, double> newAnchor) {
        this->anchor = newAnchor;
    }

    void Region::setScrollValue(ScrollType newScrollValue) {
        this->scrollValue = newScrollValue;
    }


}
