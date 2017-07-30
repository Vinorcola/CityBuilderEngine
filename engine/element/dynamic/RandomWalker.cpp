#include "RandomWalker.hpp"

#include <QDebug>

#include "engine/random.hpp"



RandomWalker::RandomWalker(const RoadGraph& roadGraph, QWeakPointer<AbstractProcessableStaticMapElement> issuer, const int walkingCredit, const qreal speed) :
    TargetedWalker(roadGraph, issuer, speed),
    walkingCredit(walkingCredit)
{
    qDebug() << "  - Create random walker at" << issuer.toStrongRef()->getEntryPoint().toString();
}



MapCoordinates RandomWalker::findNextGoingToLocation(const CycleDate& date)
{
    // Update walking credit
    --walkingCredit;
    if (walkingCredit == -1) {
        qDebug() << "  - Walker out of credits.";

        // Walking credit expires. Switch to targeted walker.
        assignTarget(issuer);

        return TargetedWalker::findNextGoingToLocation(date);
    }
    if (walkingCredit < -1) {
        return TargetedWalker::findNextGoingToLocation(date);
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
