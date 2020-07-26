#include "PathFinderNode.hpp"



PathFinderNode::PathFinderNode(
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



void PathFinderNode::updateCostIfBetter(const qreal cost)
{
    if (cost < costFromOrigin) {
        costFromOrigin = cost;
    }
}



const MapCoordinates& PathFinderNode::getLocation() const
{
    return location;
}



bool PathFinderNode::isDestination() const
{
    return straightDistanceToDestination == 0.0;
}



qreal PathFinderNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



QList<MapCoordinates> PathFinderNode::getNeighbours() const
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



bool PathFinderNode::isTheoreticallyCloserToDestinationThan(const PathFinderNode& other) const
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
