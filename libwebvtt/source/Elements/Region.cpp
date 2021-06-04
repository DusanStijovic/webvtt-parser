//
// Created by Dušan on 6/3/2021.
//

#include <algorithm>
#include <iterator>
#include "Region.h"


namespace WebVTT{

std::shared_ptr<Region>
Region::getRegionByIdentifier(const std::list<std::shared_ptr<Region>> &regions, std::u32string_view identifier)
{
    auto begin = std::make_reverse_iterator(regions.begin());
    auto end = std::make_reverse_iterator(regions.end());
    auto found = std::find_if(begin, end, [&identifier](std::shared_ptr<Region> region)
                              { return region->identifier.compare(identifier) == 0; });
    if (found == end)
        return nullptr;
    else
        return *found;
}

}
