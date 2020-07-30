#include "PathNode.hpp"



PathNode::PathNode(const MapCoordinates& location, const qreal costFromOrigin) :
    location(location),
    costFromOrigin(costFromOrigin)
{

}



const MapCoordinates& PathNode::getLocation() const
{
    return location;
}



qreal PathNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



QList<MapCoordinates> PathNode::getNeighbours() const
{
    QList<MapCoordinates> list;
    list.append(location.getNorth());
    list.append(location.getEast());
    list.append(location.getSouth());
    list.append(location.getWest());
    list.append(location.getTop());
    list.append(location.getRight());
    list.append(location.getBottom());
    list.append(location.getLeft());

    return list;
}
