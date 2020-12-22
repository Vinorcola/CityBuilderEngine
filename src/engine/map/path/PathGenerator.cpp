#include "PathGenerator.hpp"

#include "src/engine/map/path/algorithm/ClosestPathFinder.hpp"
#include "src/engine/map/path/algorithm/ShortestPathFinder.hpp"
#include "src/engine/map/path/RandomRoadPath.hpp"
#include "src/engine/map/path/TargetedPath.hpp"
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
        ShortestPathFinder::getShortestPath(origin, destination, false)
    ));
}



QSharedPointer<PathInterface> PathGenerator::generateShortestRoadPathTo(
    const Tile& origin,
    const Tile& destination
) const {

    return QSharedPointer<PathInterface>(new TargetedPath(
        true,
        ShortestPathFinder::getShortestPath(origin, destination, true)
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
    TileMatcher match
) const {

    auto path(ClosestPathFinder::getShortestPathToClosestMatch(origin, match));
    if (path.isEmpty()) {
        return nullptr;
    }

    return QSharedPointer<PathInterface>(new TargetedPath(false, path));
}



QList<const Tile*> PathGenerator::generateShortestPathForRoad(
    const Tile& origin,
    const Tile& destination
) const {

    return ShortestPathFinder::getShortestRoadablePath(origin, destination);
}
