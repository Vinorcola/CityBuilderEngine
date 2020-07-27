#include "TargetedPath.hpp"

#include "src/engine/map/path/MapDetailsInterface.hpp"



TargetedPath::TargetedPath(
    const MapDetailsInterface& mapDetails,
    const bool restrictedToRoads,
    const QList<MapCoordinates>& path
) :
    mapDetails(mapDetails),
    restrictedToRoads(restrictedToRoads),
    path(path)
{

}



MapCoordinates TargetedPath::getNextTargetCoordinates()
{
    if (path.isEmpty()) {
        return {};
    }

    auto nextLocation(path.takeFirst());
    if (!mapDetails.isLocationTraversable(nextLocation)) {
        return {};
    }
    if (restrictedToRoads && !mapDetails.hasRoadAtLocation(nextLocation)) {
        return {};
    }

    return nextLocation;
}
