#include "Road.hpp"





Road::Road(RoadGraphNode* graphNode) :
    AbstractBuilding(MapArea(graphNode->getCoordinates())),
    graphNode(graphNode)
{

}
