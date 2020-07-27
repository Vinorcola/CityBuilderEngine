#include "TargetedPath.hpp"

#include "src/engine/map/path/MapDetailsInterface.hpp"
#include "src/engine/map/pathFinder/PathFinder.hpp"



TargetedPath::TargetedPath(
    const MapDetailsInterface& mapDetails,
    const PathFinder& pathFinder,
    const MapCoordinates& initialLocation,
    const MapCoordinates& destination,
    const bool restrictedToRoads
) :
    mapDetails(mapDetails),
    pathFinder(pathFinder),
    currentLocation(initialLocation.getRounded()),
    destination(destination),
    restrictedToRoads(restrictedToRoads),
    path(pathFinder.getShortestPath(initialLocation, destination, restrictedToRoads))
{

}



MapCoordinates TargetedPath::getNextTargetCoordinates()
{
    auto nextLocation(path.takeFirst());
    if (!mapDetails.isLocationTraversable(nextLocation)) {
        recalculatePath();
        nextLocation = path.takeFirst();
    }
    else if (restrictedToRoads && !mapDetails.isLocationARoad(nextLocation)) {
        recalculatePath();
        nextLocation = path.takeFirst();
    }

    currentLocation = nextLocation;

    return nextLocation;
}



void TargetedPath::recalculatePath()
{
    path = pathFinder.getShortestPath(currentLocation, destination, restrictedToRoads);
}
