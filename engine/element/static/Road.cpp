#include "Road.hpp"



Road::Road(const StaticElementInformation* conf, const MapCoordinates& coordinates) :
    AbstractStaticMapElement(conf, MapArea(coordinates))
{

}
