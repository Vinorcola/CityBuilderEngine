#include "TargetedPath.hpp"

#include "src/engine/map/path/MapDetailsInterface.hpp"



TargetedPath::TargetedPath(
    const MapDetailsInterface& mapDetails,
    const bool restrictedToRoads,
    const QList<TileCoordinates>& path
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



bool TargetedPath::isNextTargetCoordinatesValid() const
{
    if (obsolete || path.isEmpty()) {
        return false;
    }

    auto nextLocation(path.first());
    if (!mapDetails.isLocationTraversable(nextLocation)) {
        obsolete = true;
        return false;
    }
    if (restrictedToRoads && !mapDetails.hasRoadAtLocation(nextLocation)) {
        obsolete = true;
        return false;
    }

    return true;
}



TileCoordinates TargetedPath::getNextValidTargetCoordinates()
{
    return path.takeFirst();
}



const QList<TileCoordinates>& TargetedPath::toCoordinatesList() const
{
    return path;
}
