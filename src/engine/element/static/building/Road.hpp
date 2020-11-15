#ifndef ROAD_HPP
#define ROAD_HPP

#include "src/engine/element/static/building/Building.hpp"

class BuildingInformation;
class MapCoordinates;

/**
 * @brief A road.
 *
 * Roads are very particular buildings. They constitute a road graph on wich the dynamic elements will move. Check
 * RoadGraph for more information.
 */
class Road : public Building
{
        Q_OBJECT

    public:
        Road(QObject* parent, const BuildingInformation& conf, const MapCoordinates& coordinates);
};

#endif // ROAD_HPP
