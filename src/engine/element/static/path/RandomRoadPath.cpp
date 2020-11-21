#include "RandomRoadPath.hpp"

#include <QRandomGenerator>

#include "src/engine/element/static/path/MapDetailsInterface.hpp"



RandomRoadPath::RandomRoadPath(
    const MapDetailsInterface& mapDetails,
    const MapCoordinates& initialLocation,
    const int wanderingCredits
) :
    mapDetails(mapDetails),
    previousLocation(),
    currentLocation(initialLocation.getRounded()),
    wanderingCredits(wanderingCredits)
{

}



bool RandomRoadPath::isObsolete() const
{
    return false;
}



bool RandomRoadPath::isCompleted() const
{
    return wanderingCredits <= 0;
}



MapCoordinates RandomRoadPath::getNextTargetCoordinates()
{
    auto nextLocation(getNextRandomCoordinates());
    if (!nextLocation.isValid()) {
        return nextLocation;
    }

    previousLocation = currentLocation;
    currentLocation = nextLocation;
    --wanderingCredits;

    return currentLocation;
}



MapCoordinates RandomRoadPath::getNextRandomCoordinates() const
{
    if (wanderingCredits <= 0) {
        // Wandering credits expired.
        return {};
    }

    QList<MapCoordinates> neighbours({
        currentLocation.getNorth(),
        currentLocation.getEast(),
        currentLocation.getSouth(),
        currentLocation.getWest(),
    });
    QList<MapCoordinates> roadNeighbours;
    for (auto neighbour : neighbours) {
        if (mapDetails.hasRoadAtLocation(neighbour)) {
            roadNeighbours.append(neighbour);
        }
    }

    if (roadNeighbours.size() == 0) {
        // Character is on a single road tile.
        return {};
    }
    if (roadNeighbours.size() == 1) {
        // Dead end, must go back.
        return roadNeighbours.first();
    }

    // We remove the previous node to avoid going back on a bifurcation.
    if (previousLocation.isValid()) {
        roadNeighbours.removeOne(previousLocation);
    }

    if (roadNeighbours.size() == 1) {
        // Only one choice left
        return roadNeighbours.first();
    }

    // Choose random.
    return roadNeighbours.at(QRandomGenerator::global()->bounded(0, roadNeighbours.size()));
}
