#include "PathGenerator.hpp"

#include "src/engine/map/path/RandomRoadPath.hpp"
#include "src/engine/map/path/TargetedPath.hpp"



PathGenerator::PathGenerator(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails),
    closestPathFinder(mapDetails),
    shortestPathFinder(mapDetails)
{

}



owner<PathInterface*> PathGenerator::generateWanderingPath(
    const MapCoordinates& origin,
    const int wanderingCredits
) const {

    return new RandomRoadPath(mapDetails, origin, wanderingCredits);
}



owner<PathInterface*> PathGenerator::generateShortestPathTo(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    return new TargetedPath(mapDetails, false, shortestPathFinder.getShortestPath(origin, destination, false));
}



owner<PathInterface*> PathGenerator::generateShortestRoadPathTo(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    return new TargetedPath(mapDetails, true, shortestPathFinder.getShortestPath(origin, destination, true));
}



optional<owner<PathInterface*>> PathGenerator::generateShortestPathToClosestMatch(
    const MapCoordinates& origin,
    std::function<bool (const MapCoordinates&)> match
) const {

    auto path(closestPathFinder.getShortestPathToClosestMatch(origin, match));
    if (path.isEmpty()) {
        return nullptr;
    }

    return new TargetedPath(mapDetails, false, path);
}
