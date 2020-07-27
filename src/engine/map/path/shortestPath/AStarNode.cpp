#include "AStarNode.hpp"



AStarNode::AStarNode(
    const MapCoordinates& location,
    const MapCoordinates& destination,
    const qreal cost,
    const bool useDiagonals
) :
    location(location),
    costFromOrigin(cost),
    theoreticalBestDistanceToDestination(
        useDiagonals ?
            location.getChebyshevDistanceTo(destination) :
            location.getManhattanDistanceTo(destination)
    ),
    straightDistanceToDestination(location.getStraightDistanceTo(destination)),
    useDiagonals(useDiagonals)
{

}



void AStarNode::updateCostIfBetter(const qreal cost)
{
    if (cost < costFromOrigin) {
        costFromOrigin = cost;
    }
}



const MapCoordinates& AStarNode::getLocation() const
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



QList<MapCoordinates> AStarNode::getNeighbours() const
{
    QList<MapCoordinates> list;
    list.append(location.getNorth());
    list.append(location.getEast());
    list.append(location.getSouth());
    list.append(location.getWest());
    if (useDiagonals) {
        list.append(location.getTop());
        list.append(location.getRight());
        list.append(location.getBottom());
        list.append(location.getLeft());
    }

    return list;
}



bool AStarNode::isTheoreticallyCloserToDestinationThan(const AStarNode& other) const
{
    auto thisBestCost(costFromOrigin + theoreticalBestDistanceToDestination);
    auto otherBestCost(other.costFromOrigin + other.theoreticalBestDistanceToDestination);

    if (thisBestCost < otherBestCost) {
        return true;
    }

    if (thisBestCost> otherBestCost) {
        return false;
    }

    // Best costs are equals, we use straight distance to decide.

    return straightDistanceToDestination < other.straightDistanceToDestination;
}
