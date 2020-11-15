#include "Road.hpp"



Road::Road(const BuildingInformation& conf, const MapCoordinates& coordinates) :
    AbstractBuilding(conf, MapArea(coordinates))
{

}
