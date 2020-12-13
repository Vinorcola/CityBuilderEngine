#include "PathGenerator.hpp"

#include "src/engine/map/path/RandomRoadPath.hpp"
#include "src/engine/map/path/TargetedPath.hpp"



PathGenerator::PathGenerator(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails),
    closestPathFinder(mapDetails),
    shortestPathFinder(mapDetails)
{

}



QSharedPointer<PathInterface> PathGenerator::generateWanderingPath(
    const MapCoordinates& origin,
    const int wanderingCredits
) const {

    return QSharedPointer<PathInterface>(new RandomRoadPath(
        mapDetails,
        origin,
        wanderingCredits
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestPathTo(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        mapDetails,
        false,
        shortestPathFinder.getShortestPath(origin, destination, false)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestRoadPathTo(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        mapDetails,
        true,
        shortestPathFinder.getShortestPath(origin, destination, true)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generatePreferedShortestPathTo(
    const MapCoordinates& origin,
    const MapCoordinates& destination,
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
    const MapCoordinates& origin,
    std::function<bool (const MapCoordinates&)> match
) const {

    auto path(closestPathFinder.getShortestPathToClosestMatch(origin, match));
    if (path.isEmpty()) {
        return nullptr;
    }

    return QSharedPointer<PathInterface>(new TargetedPath(mapDetails, false, path));
}



QList<MapCoordinates> PathGenerator::generateShortestPathForRoad(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    return shortestPathFinder.getShortestRoadablePath(origin, destination);
}
