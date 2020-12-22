#ifndef NATUREELEMENTSTATE_HPP
#define NATUREELEMENTSTATE_HPP

#include "src/global/geometry/TileArea.hpp"

class NatureElementInformation;

struct NatureElementState
{
    NatureElementState(qintptr id, const NatureElementInformation& type, const TileArea& area) :
        id(id),
        type(type),
        area(area)
    {}

    NatureElementState(const NatureElementState& other) :
        id(other.id),
        type(other.type),
        area(other.area)
    {}

    NatureElementState& operator=(const NatureElementState& other)
    {
        if (this != &other) {
            this->~NatureElementState();
            new(this) NatureElementState(other);
        }

        return *this;
    }

    qintptr id;
    const NatureElementInformation& type;
    TileArea area;
};

#endif // NATUREELEMENTSTATE_HPP
