#include "PathGenerator.hpp"

#include "src/engine/map/path/algorithm/PathFinder.hpp"
#include "src/engine/map/path/RandomRoadPath.hpp"
#include "src/engine/map/path/TargetedPath.hpp"
#include "src/engine/map/Tile.hpp"
#include "src/global/geometry/DynamicElementCoordinates.hpp"



QSharedPointer<PathInterface> PathGenerator::generateWanderingPath(
    const Tile& origin,
    const int wanderingCredits
) const {

    return QSharedPointer<PathInterface>(new RandomRoadPath(origin, wanderingCredits));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestPathTo(
    const Tile& origin,
    const Tile& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        false,
        PathFinder::getShortestPath(origin, destination, false)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestRoadPathTo(
    const Tile& origin,
    const Tile& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        true,
        PathFinder::getShortestPath(origin, destination, true)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generatePreferedShortestPathTo(
    const Tile& origin,
    const Tile& destination,
    bool restrictedToRoads
) const {

    auto roadPath(generateShortestRoadPathTo(origin, destination));
    if (roadPath) {
        return roadPath;
    }

    if (restrictedToRoads) {
        return {};
    }

    return generateShortestPathTo(origin, destination);
}



QSharedPointer<PathInterface> PathGenerator::generateShortestPathToClosestMatch(
    const Tile& origin,
    TargetFetcher getTarget
) const {

    auto path(PathFinder::getShortestPathToClosestMatch(origin, getTarget));
    if (path.isEmpty()) {
        return {};
    }

    auto target(getTarget(*path.last()));
    if (!path.last()->isTraversable()) {
        // The target may not be traversable, we remove it from the path.
        path.removeLast();
    }

    return QSharedPointer<PathInterface>(new TargetedPath(false, path, target));
}



QList<const Tile*> PathGenerator::generateShortestPathForRoad(
    const Tile& origin,
    const Tile& destination
) const {

    return PathFinder::getShortestRoadablePath(origin, destination);
}
