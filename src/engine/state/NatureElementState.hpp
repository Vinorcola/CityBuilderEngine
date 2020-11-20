#ifndef NATUREELEMENTSTATE_HPP
#define NATUREELEMENTSTATE_HPP

#include "src/engine/map/MapArea.hpp"

class NatureElementInformation;

struct NatureElementState
{
    NatureElementState(const NatureElementInformation& type, const MapArea& area) :
        type(type),
        area(area)
    {}

    const NatureElementInformation& type;
    MapArea area;
};

#endif // NATUREELEMENTSTATE_HPP
