#include "PathGenerator.hpp"

#include "src/engine/map/path/RandomRoadPath.hpp"
#include "src/engine/map/path/TargetedPath.hpp"
#include "src/global/geometry/DynamicElementCoordinates.hpp"



PathGenerator::PathGenerator(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails),
    closestPathFinder(mapDetails),
    shortestPathFinder(mapDetails)
{

}



QSharedPointer<PathInterface> PathGenerator::generateWanderingPath(
    const TileCoordinates& origin,
    const int wanderingCredits
) const {

    return QSharedPointer<PathInterface>(new RandomRoadPath(
        mapDetails,
        origin,
        wanderingCredits
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestPathTo(
    const TileCoordinates& origin,
    const TileCoordinates& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        mapDetails,
        false,
        shortestPathFinder.getShortestPath(origin, destination, false)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestPathTo(
    const DynamicElementCoordinates& origin,
    const TileCoordinates& destination
) const {

    // TODO: To correct later.
    return generateShortestPathTo(origin.associatedTileCoordinates(), destination);
}



QSharedPointer<PathInterface> PathGenerator::generateShortestRoadPathTo(
    const TileCoordinates& origin,
    const TileCoordinates& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        mapDetails,
        true,
        shortestPathFinder.getShortestPath(origin, destination, true)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestRoadPathTo(
    const DynamicElementCoordinates& origin,
    const TileCoordinates& destination
) const {

    // TODO: To correct later.
    return generateShortestRoadPathTo(origin.associatedTileCoordinates(), destination);
}



QSharedPointer<PathInterface> PathGenerator::generatePreferedShortestPathTo(
    const TileCoordinates& origin,
    const TileCoordinates& destination,
    bool restrictedToRoads
) const {

    auto roadPath(generateShortestRoadPathTo(origin, destination));
    if (roadPath) {
        return roadPath;
    }

    if (restrictedToRoads) {
        return nullptr;
    }

    return generateShortestPathTo(origin, destination);
}



QSharedPointer<PathInterface> PathGenerator::generateShortestPathToClosestMatch(
    const TileCoordinates& origin,
    std::function<bool (const TileCoordinates&)> match
) const {

    auto path(closestPathFinder.getShortestPathToClosestMatch(origin, match));
    if (path.isEmpty()) {
        return nullptr;
    }

    return QSharedPointer<PathInterface>(new TargetedPath(mapDetails, false, path));
}



QList<TileCoordinates> PathGenerator::generateShortestPathForRoad(
    const TileCoordinates& origin,
    const TileCoordinates& destination
) const {

    return shortestPathFinder.getShortestRoadablePath(origin, destination);
}
