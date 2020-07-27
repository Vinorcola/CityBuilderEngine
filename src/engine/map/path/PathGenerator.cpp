#include "PathGenerator.hpp"

#include "src/engine/map/path/RandomRoadPath.hpp"
#include "src/engine/map/path/TargetedPath.hpp"



PathGenerator::PathGenerator(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails),
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
