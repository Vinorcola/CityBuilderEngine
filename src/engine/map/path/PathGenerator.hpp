#ifndef PATHGENERATOR_HPP
#define PATHGENERATOR_HPP

#include "src/engine/map/path/shortestPath/ShortestPathFinder.hpp"
#include "src/defines.hpp"

class MapCoordinates;
class MapDetailsInterface;
class PathInterface;

class PathGenerator
{
    private:
        const MapDetailsInterface& mapDetails;
        ShortestPathFinder shortestPathFinder;

    public:
        explicit PathGenerator(const MapDetailsInterface& mapDetails);

        /**
         * @brief Generate a path for a wandering character.
         */
        owner<PathInterface*> generateWanderingPath(const MapCoordinates& origin, const int wanderingCredits) const;

        /**
         * @brief Generate the shortest path from origin to target.
         */
        owner<PathInterface*> generateShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const;

        /**
         * @brief Generate the shortest path from origin to target by using roads only.
         */
        owner<PathInterface*> generateShortestRoadPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const;
};

#endif // PATHGENERATOR_HPP