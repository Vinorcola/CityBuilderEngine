#include "AStarNode.hpp"

#include <QtCore/QList>



AStarNode::AStarNode(
    const TileCoordinates& location,
    const TileCoordinates& destination,
    const qreal cost,
    const bool useDiagonals
) :
    location(location),
    costFromOrigin(cost),
    theoreticalBestDistanceToDestination(
        useDiagonals ?
            location.chebyshevDistanceTo(destination) :
            location.manhattanDistanceTo(destination)
    ),
    straightDistanceToDestination(location.straightDistanceTo(destination))
{

}



void AStarNode::updateCostIfBetter(const qreal cost)
{
    if (cost < costFromOrigin) {
        costFromOrigin = cost;
    }
}



const TileCoordinates& AStarNode::getLocation() const
{
    return location;
}



bool AStarNode::isDestination() const
{
    return straightDistanceToDestination == 0.0;
}



qreal AStarNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



QList<TileCoordinates> AStarNode::getNeighbours() const
{
    QList<TileCoordinates> list;
    list.append({ location.x(), location.y() - 1 }); // North
    list.append({ location.x(), location.y() + 1 }); // South
    list.append({ location.x() + 1, location.y() }); // East
    list.append({ location.x() - 1, location.y() }); // West

    return list;
}



QList<TileCoordinates> AStarNode::getDiagonalNeighbours() const
{
    QList<TileCoordinates> list;
    list.append({ location.x() + 1, location.y() - 1 }); // Top
    list.append({ location.x() - 1, location.y() + 1 }); // Bottom
    list.append({ location.x() - 1, location.y() - 1}); // Left
    list.append({ location.x() + 1, location.y() + 1}); // Right

    return list;
}



bool AStarNode::isTheoreticallyCloserToDestinationThan(const AStarNode& other) const
{
    auto thisBestCost(costFromOrigin + theoreticalBestDistanceToDestination);
    auto otherBestCost(other.costFromOrigin + other.theoreticalBestDistanceToDestination);

    return thisBestCost <= otherBestCost;
}
