#include "Road.hpp"



Road::Road(QObject* parent, const BuildingInformation* conf, const MapCoordinates& coordinates) :
    Building(parent, conf, MapArea(coordinates))
{

}
