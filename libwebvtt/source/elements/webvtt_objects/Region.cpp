#include "elements/webvtt_objects/Region.h"
#include <algorithm>
#include <iterator>

namespace WebVTT
{

     void Region::setIdentifier(const std::u32string_view newIdentifier)
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
