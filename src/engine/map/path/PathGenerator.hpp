#ifndef PATHGENERATOR_HPP
#define PATHGENERATOR_HPP

#include "src/engine/map/path/closestPath/ClosestPathFinder.hpp"
#include "src/engine/map/path/shortestPath/ShortestPathFinder.hpp"
#include "src/engine/map/path/PathGeneratorInterface.hpp"

class MapCoordinates;
class MapDetailsInterface;

class PathGenerator : public PathGeneratorInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        ClosestPathFinder closestPathFinder;
        ShortestPathFinder shortestPathFinder;

    public:
        explicit PathGenerator(const MapDetailsInterface& mapDetails);

        virtual QSharedPointer<PathInterface> generateWanderingPath(
            const MapCoordinates& origin,
            const int wanderingCredits
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const override;

        virtual QSharedPointer<PathInterface> generatePreferedShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination,
            bool restrictedToRoads
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestPathToClosestMatch(
            const MapCoordinates& origin,
            std::function<bool(const MapCoordinates&)> match
        ) const override;

        QList<MapCoordinates> generateShortestPathForRoad(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const;
};

#endif // PATHGENERATOR_HPP
