#ifndef ROAD_HPP
#define ROAD_HPP

#include "src/engine/element/static/building/AbstractBuilding.hpp"

class BuildingInformation;
class MapCoordinates;

/**
 * @brief A road.
 *
 * Roads are very particular buildings. They constitute a road graph on wich the dynamic elements will move. Check
 * RoadGraph for more information.
 */
class Road : public AbstractBuilding
{
    public:
        Road(const BuildingInformation& conf, const MapCoordinates& coordinates);
};

#endif // ROAD_HPP
