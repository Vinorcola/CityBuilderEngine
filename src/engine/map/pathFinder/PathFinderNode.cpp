#include "PathFinderNode.hpp"



PathFinderNode::PathFinderNode(const MapCoordinates& location, const MapCoordinates& destination, const qreal cost) :
    location(location),
    costFromOrigin(cost),
    manhattanDistanceToDestination(location.getManhattanDistanceTo(destination)),
    straightDistanceToDestination(location.getStraightDistanceTo(destination))
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



QList<MapCoordinates> PathFinderNode::getNeighbours(const bool includeDiagonalDirections) const
{
    QList<MapCoordinates> list;
    list.append(location.getNorth());
    list.append(location.getEast());
    list.append(location.getSouth());
    list.append(location.getWest());
    if (includeDiagonalDirections) {
        list.append(location.getTop());
        list.append(location.getRight());
        list.append(location.getBottom());
        list.append(location.getLeft());
    }

    return list;
}



bool PathFinderNode::isTheoreticallyCloserToDestinationThan(const PathFinderNode& other) const
{
    auto thisBestCost(getTheoreticalBestCostToReachDestination());
    auto otherBestCost(other.getTheoreticalBestCostToReachDestination());

    if (thisBestCost < otherBestCost) {
        return true;
    }

    if (thisBestCost> otherBestCost) {
        return false;
    }

    // Best costs are equals, we use straight distance to decide.

    return straightDistanceToDestination < other.straightDistanceToDestination;
}



qreal PathFinderNode::getTheoreticalBestCostToReachDestination() const
{
    return costFromOrigin + manhattanDistanceToDestination;
}
