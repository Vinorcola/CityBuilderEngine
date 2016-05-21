#include "RandomWalker.hpp"

#include <QDebug>

#include "engine/random.hpp"





RandomWalker::RandomWalker(const RoadGraph& roadGraph, const MapCoordinates& initialLocation) :
    AbstractCharacter(initialLocation),
    roadGraph(roadGraph)
{
    qDebug() << "  - Create random walker at" << initialLocation.toString();
}





MapCoordinates RandomWalker::getNextTargetLocation()
{
    auto list(roadGraph.getNextNodeList(getPreviousLocation(), getCurrentLocation()));

    if (list.size() == 0)
    {
        // No solutions, return invalid coordinates.
        return MapCoordinates();
    }

    if (list.size() == 1)
    {
        // Only one solution, return its coordinates.
        return list.first()->getCoordinates();
    }

    // Choose random.
    int randomNum(randomInt(0, list.size() - 1));
    return list.at(randomNum)->getCoordinates();
}
