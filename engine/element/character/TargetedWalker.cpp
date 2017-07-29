#include "TargetedWalker.hpp"



TargetedWalker::TargetedWalker(const RoadGraph& roadGraph, QWeakPointer<AbstractProcessableBuilding> issuer, const qreal speed) :
    AbstractCharacter(issuer, speed),
    targetBuilding(),
    targetLocation(issuer.toStrongRef()->getEntryPoint()),
    path(),
    roadGraph(roadGraph)
{

}



void TargetedWalker::assignTarget(QWeakPointer<AbstractProcessableBuilding> targetAccess)
{
    auto target(targetAccess.toStrongRef());
    if (target) {
        targetBuilding = targetAccess;
        targetLocation = target->getEntryPoint();
        path.clear();
        path = roadGraph.getShortestPathBetween(getCurrentLocation(), targetLocation);
        if (path.first()->getCoordinates() == getCurrentLocation()) {
            path.takeFirst();
        }
    }
}



bool TargetedWalker::hasTarget() const
{
    return targetBuilding;
}



bool TargetedWalker::hasReachableTarget() const
{
    return targetBuilding && (
        !path.isEmpty() || (path.isEmpty() && getGoingToLocation() == targetLocation)
    );
}



bool TargetedWalker::reachedTarget() const
{
    return targetBuilding && path.isEmpty() && getCurrentLocation() == targetLocation;
}



MapCoordinates TargetedWalker::findNextGoingToLocation(const CycleDate& date)
{
    if (path.isEmpty()) {
        if (targetBuilding && getCurrentLocation() == targetLocation) {
            // Reached target.
            auto target(targetBuilding.toStrongRef());
            if (target) {
                target->processInteraction(date, this);
            }
        }

        // No path to follow, character stays where it is.
        return getCurrentLocation();
    }

    return path.takeFirst()->getCoordinates();
}
