#include "TargetedWalker.hpp"

#include "engine/map/roadGraph/RoadGraph.hpp"
#include "engine/map/roadGraph/RoadGraphNode.hpp"



TargetedWalker::TargetedWalker(
    QObject* parent,
    const DynamicElementInformation* conf,
    const RoadGraph& roadGraph,
    AbstractProcessableStaticMapElement* issuer
) :
    AbstractDynamicMapElement(parent, conf, issuer),
    targetElement(),
    targetLocation(issuer->getEntryPoint()),
    path(),
    roadGraph(roadGraph)
{

}



void TargetedWalker::assignTarget(AbstractProcessableStaticMapElement* target)
{
    targetElement = target;
    path.clear();
    if (target) {
        targetLocation = target->getEntryPoint();
        path = roadGraph.getShortestPathBetween(getCurrentLocation(), targetLocation);
        if (!path.isEmpty() && path.first()->getCoordinates() == getCurrentLocation()) {
            path.takeFirst();
        }
    } else {
        targetLocation = MapCoordinates();
    }
}



bool TargetedWalker::hasTarget() const
{
    return targetElement;
}



bool TargetedWalker::hasReachableTarget() const
{
    return targetElement && (
        !path.isEmpty() || (path.isEmpty() && getGoingToLocation() == targetLocation)
    );
}



bool TargetedWalker::reachedTarget() const
{
    return targetElement && path.isEmpty() && getCurrentLocation() == targetLocation;
}



MapCoordinates TargetedWalker::findNextGoingToLocation(const CycleDate& date)
{
    if (path.isEmpty()) {
        if (targetElement && getCurrentLocation() == targetLocation) {
            // Reached target.
            targetElement->processInteraction(date, this);
        }

        // No path to follow, character stays where it is.
        return getCurrentLocation();
    }

    return path.takeFirst()->getCoordinates();
}
