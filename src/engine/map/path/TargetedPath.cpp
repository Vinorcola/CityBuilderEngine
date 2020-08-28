#include "TargetedPath.hpp"

#include "src/engine/map/path/MapDetailsInterface.hpp"



TargetedPath::TargetedPath(
    const MapDetailsInterface& mapDetails,
    const bool restrictedToRoads,
    const QList<MapCoordinates>& path
) :
    mapDetails(mapDetails),
    restrictedToRoads(restrictedToRoads),
    path(path),
    obsolete(false)
{

}



bool TargetedPath::isObsolete() const
{
    return obsolete;
}



bool TargetedPath::isCompleted() const
{
    return path.isEmpty();
}



MapCoordinates TargetedPath::getNextTargetCoordinates()
{
    if (path.isEmpty()) {
        return {};
    }

    auto nextLocation(path.takeFirst());
    if (!mapDetails.isLocationTraversable(nextLocation)) {
        obsolete = true;
        return {};
    }
    if (restrictedToRoads && !mapDetails.hasRoadAtLocation(nextLocation)) {
        obsolete = true;
        return {};
    }

    return nextLocation;
}
