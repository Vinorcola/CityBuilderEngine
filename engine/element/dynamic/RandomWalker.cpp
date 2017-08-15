#include "RandomWalker.hpp"

#include "engine/map/roadGraph/RoadGraph.hpp"
#include "engine/map/roadGraph/RoadGraphNode.hpp"
#include "engine/random.hpp"
#include "global/conf/DynamicElementInformation.hpp"



RandomWalker::RandomWalker(
    QObject* parent,
    const DynamicElementInformation* conf,
    const RoadGraph* roadGraph,
    AbstractProcessableStaticMapElement* issuer
) :
    TargetedWalker(parent, conf, roadGraph, issuer),
    walkingCredit(conf->getWalkingCredit())
{

}



void RandomWalker::assignTarget(AbstractProcessableStaticMapElement* targetElement)
{
    walkingCredit = -2;
    TargetedWalker::assignTarget(targetElement);
}



MapCoordinates RandomWalker::findNextGoingToLocation(const CycleDate& date)
{
    // Update walking credit
    --walkingCredit;
    if (walkingCredit == -1) {
        // Walking credit expires. Switch to targeted walker.
        assignTarget(issuer);

        return TargetedWalker::findNextGoingToLocation(date);
    }
    if (walkingCredit < -1) {
        return TargetedWalker::findNextGoingToLocation(date);
    }

    // Continue random walking.
    auto list(roadGraph->getNextNodeList(getComingFromLocation(), getCurrentLocation()));
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
