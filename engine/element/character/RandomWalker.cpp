#include "RandomWalker.hpp"

#include <QDebug>

#include "engine/random.hpp"



RandomWalker::RandomWalker(const RoadGraph& roadGraph, const MapCoordinates& initialLocation, const int walkingCredit, const qreal speed) :
    TargetedWalker(roadGraph, initialLocation, speed),
    walkingCredit(walkingCredit)
{
    qDebug() << "  - Create random walker at" << initialLocation.toString();
}



MapCoordinates RandomWalker::findNextGoingToLocation()
{
    // Update walking credit
    --walkingCredit;
    if (walkingCredit == -1) {
        qDebug() << "  - Walker out of credits.";

        // Walking credit expires. Switch to targeted walker.
        assignTarget(getInitialLocation());

        return TargetedWalker::findNextGoingToLocation();
    }
    if (walkingCredit < -1) {
        return TargetedWalker::findNextGoingToLocation();
    }

    // Continue random walking.
    auto list(roadGraph.getNextNodeList(getComingFromLocation(), getCurrentLocation()));
    if (list.size() == 0) {
        // No solutions, character stays where it is.
        return getCurrentLocation();
    }
    if (list.size() == 1) {
        return list.first()->getCoordinates();
    }

    // Choose random.
    return list.at(randomInt(0, list.size() - 1))->getCoordinates();
}
