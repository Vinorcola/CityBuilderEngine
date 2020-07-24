#include "Road.hpp"



Road::Road(QObject* parent, const StaticElementInformation* conf, const MapCoordinates& coordinates) :
    Building(parent, conf, MapArea(coordinates))
{

}
