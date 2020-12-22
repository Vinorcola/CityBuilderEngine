#ifndef ROAD_HPP
#define ROAD_HPP

#include "src/engine/map/staticElement/building/AbstractBuilding.hpp"

/**
 * @brief A road.
 *
 * Roads are very particular buildings. They constitute a road graph on wich the dynamic elements will move.
 */
class Road : public AbstractBuilding
{
    public:
        Road(const BuildingInformation& conf, const TileArea& area, Direction orientation);
};

#endif // ROAD_HPP
