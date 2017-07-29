#include "TargetedWalker.hpp"



TargetedWalker::TargetedWalker(const RoadGraph& roadGraph, const MapCoordinates& initialPosition) :
    AbstractCharacter(initialPosition),
    targetLocation(initialPosition),
    path(),
    hasTargetBeenAssigned(false),
    roadGraph(roadGraph)
{

}



void TargetedWalker::assignTarget(const MapCoordinates& target)
{
    hasTargetBeenAssigned = true;
    targetLocation = target;
    path.clear();
    path = roadGraph.getShortestPathBetween(getCurrentLocation(), target);
}



bool TargetedWalker::hasTarget() const
{
    return hasTargetBeenAssigned;
}



bool TargetedWalker::hasReachableTarget() const
{
    return hasTargetBeenAssigned && (
        !path.isEmpty() || (path.isEmpty() && getGoingToLocation() == targetLocation)
    );
}



bool TargetedWalker::reachedTarget() const
{
    return hasTargetBeenAssigned && path.isEmpty() && getCurrentLocation() == targetLocation;
}



MapCoordinates TargetedWalker::findNextGoingToLocation()
{
    if (path.isEmpty()) {
        // No path to follow, character stays where it is.
        return getCurrentLocation();
    }

    return path.takeFirst()->getCoordinates();
}
