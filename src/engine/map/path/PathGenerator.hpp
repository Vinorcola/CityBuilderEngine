#ifndef PATHGENERATOR_HPP
#define PATHGENERATOR_HPP

#include "src/engine/element/dynamic/PathGeneratorInterface.hpp"
#include "src/engine/map/path/closestPath/ClosestPathFinder.hpp"
#include "src/engine/map/path/shortestPath/ShortestPathFinder.hpp"
#include "src/defines.hpp"

class MapCoordinates;
class MapDetailsInterface;
class PathInterface;

class PathGenerator : public PathGeneratorInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        ClosestPathFinder closestPathFinder;
        ShortestPathFinder shortestPathFinder;

    public:
        explicit PathGenerator(const MapDetailsInterface& mapDetails);

        virtual optional<owner<PathInterface*>> generateWanderingPath(
            const MapCoordinates& origin,
            const int wanderingCredits
        ) const override;

        virtual optional<owner<PathInterface*>> generateShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const override;

        virtual optional<owner<PathInterface*>> generateShortestRoadPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const override;

        virtual optional<owner<PathInterface*>> generatePreferedShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination,
            bool restrictedToRoads
        ) const override;

        virtual optional<owner<PathInterface*>> generateShortestPathToClosestMatch(
            const MapCoordinates& origin,
            std::function<bool(const MapCoordinates&)> match
        ) const override;
};

#endif // PATHGENERATOR_HPP
