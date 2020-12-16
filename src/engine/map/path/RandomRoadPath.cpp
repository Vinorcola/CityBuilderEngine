#include "RandomRoadPath.hpp"

#include <QtCore/QList>
#include <QtCore/QRandomGenerator>

#include "src/engine/map/path/MapDetailsInterface.hpp"



RandomRoadPath::RandomRoadPath(
    const MapDetailsInterface& mapDetails,
    const TileCoordinates& initialLocation,
    const int wanderingCredits
) :
    mapDetails(mapDetails),
    previousLocation(initialLocation),
    currentLocation(initialLocation),
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



bool RandomRoadPath::isNextTargetCoordinatesValid() const
{
    return wanderingCredits <= 0;
}



TileCoordinates RandomRoadPath::getNextValidTargetCoordinates()
{
    auto nextLocation(getNextRandomCoordinates());

    previousLocation = currentLocation;
    currentLocation = nextLocation;
    --wanderingCredits;

    return currentLocation;
}



TileCoordinates RandomRoadPath::getNextRandomCoordinates() const
{
    QList<TileCoordinates> neighbours({
        { currentLocation.x(), currentLocation.y() - 1 }, // North
        { currentLocation.x(), currentLocation.y() + 1 }, // South
        { currentLocation.x() + 1, currentLocation.y() }, // East
        { currentLocation.x() - 1, currentLocation.y() }, // West
    });
    QList<TileCoordinates> roadNeighbours;
    for (auto neighbour : neighbours) {
        if (mapDetails.hasRoadAtLocation(neighbour)) {
            roadNeighbours.append(neighbour);
        }
    }

    if (roadNeighbours.size() == 0) {
        // Character is on a single road tile.
        return currentLocation;
    }
    if (roadNeighbours.size() == 1) {
        // Dead end, must go back.
        return roadNeighbours.first();
    }

    // We remove the previous node to avoid going back on a bifurcation.
    if (previousLocation != currentLocation) {
        roadNeighbours.removeOne(previousLocation);
    }

    if (roadNeighbours.size() == 1) {
        // Only one choice left
        return roadNeighbours.first();
    }

    // Choose random.
    return roadNeighbours.at(QRandomGenerator::global()->bounded(0, roadNeighbours.size()));
}
