#include "PathFinderNode.hpp"



PathFinderNode::PathFinderNode(const MapCoordinates& location, const qreal cost, const MapCoordinates& target) :
    location(location),
    costFromOrigin(cost),
    manhattanDistanceToTarget(location.getManhattanDistanceTo(target)),
    straightDistanceToTarget(location.getStraightDistanceTo(target))
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



bool PathFinderNode::isTarget() const
{
    return straightDistanceToTarget == 0.0;
}



qreal PathFinderNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



bool PathFinderNode::isTheoreticallyCloserToTargetThan(const PathFinderNode& other) const
{
    auto thisBestCost(getTheoreticalBestCostToReachTarget());
    auto otherBestCost(other.getTheoreticalBestCostToReachTarget());

    if (thisBestCost < otherBestCost) {
        return true;
    }

    if (thisBestCost> otherBestCost) {
        return false;
    }

    // Best costs are equals, we use straight distance to decide.

    return straightDistanceToTarget < other.straightDistanceToTarget;
}



qreal PathFinderNode::getTheoreticalBestCostToReachTarget() const
{
    return costFromOrigin + manhattanDistanceToTarget;
}
