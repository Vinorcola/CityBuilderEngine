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



bool PathFinderNode::isTarget() const
{
    return straightDistanceToTarget == 0.0;
}



qreal PathFinderNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



qreal PathFinderNode::getTheoreticalBestCostToReachTarget() const
{
    return costFromOrigin + manhattanDistanceToTarget;
}



qreal PathFinderNode::getStraightDistanceToTarget() const
{
    return straightDistanceToTarget;
}
