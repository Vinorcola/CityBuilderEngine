#include "TargetedWalker.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



TargetedWalker::TargetedWalker(QObject* parent, const RoadGraph* roadGraph, AbstractProcessableStaticMapElement* issuer, const qreal speed) :
    AbstractDynamicMapElement(parent, issuer, speed),
    targetElement(),
    targetLocation(issuer->getEntryPoint()),
    path(),
    roadGraph(roadGraph)
{

}



void TargetedWalker::assignTarget(AbstractProcessableStaticMapElement* target)
{
    targetElement = target;
    targetLocation = target->getEntryPoint();
    path.clear();
    path = roadGraph->getShortestPathBetween(getCurrentLocation(), targetLocation);
    if (path.first()->getCoordinates() == getCurrentLocation()) {
        path.takeFirst();
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
