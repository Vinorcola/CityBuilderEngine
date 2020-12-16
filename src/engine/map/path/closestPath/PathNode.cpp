#include "PathNode.hpp"

#include <QtCore/QList>



PathNode::PathNode(const TileCoordinates& location, const qreal costFromOrigin) :
    location(location),
    costFromOrigin(costFromOrigin)
{

}



const TileCoordinates& PathNode::getLocation() const
{
    return location;
}



qreal PathNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



QList<TileCoordinates> PathNode::getNeighbours() const
{
    QList<TileCoordinates> list;
    list.append({ location.x(), location.y() - 1 }); // North
    list.append({ location.x(), location.y() + 1 }); // South
    list.append({ location.x() + 1, location.y() }); // East
    list.append({ location.x() - 1, location.y() }); // West

    return list;
}



QList<TileCoordinates> PathNode::getDiagonalNeighbours() const
{
    QList<TileCoordinates> list;
    list.append({ location.x() + 1, location.y() - 1 }); // Top
    list.append({ location.x() - 1, location.y() + 1 }); // Bottom
    list.append({ location.x() - 1, location.y() - 1}); // Left
    list.append({ location.x() + 1, location.y() + 1}); // Right

    return list;
}
