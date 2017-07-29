#ifndef ROAD_HPP
#define ROAD_HPP

#include "engine/element/building/AbstractBuilding.hpp"

/**
 * @brief A road building.
 */
class Road : public AbstractBuilding
{
    public:
        Road(const MapCoordinates& coordinates);
};

#endif // ROAD_HPP
