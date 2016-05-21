#include "Road.hpp"





Road::Road(Map& map, const MapCoordinates& coordinates) :
    AbstractBuilding(map, MapArea(coordinates)),
    graphNode(map.getRoadGraph().createNode(coordinates))
{

}
