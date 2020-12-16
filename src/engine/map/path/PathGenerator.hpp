#ifndef PATHGENERATOR_HPP
#define PATHGENERATOR_HPP

#include "src/engine/map/path/closestPath/ClosestPathFinder.hpp"
#include "src/engine/map/path/shortestPath/ShortestPathFinder.hpp"
#include "src/engine/map/path/PathGeneratorInterface.hpp"

class MapDetailsInterface;
class TileCoordinates;

class PathGenerator : public PathGeneratorInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        ClosestPathFinder closestPathFinder;
        ShortestPathFinder shortestPathFinder;

    public:
        explicit PathGenerator(const MapDetailsInterface& mapDetails);

        virtual QSharedPointer<PathInterface> generateWanderingPath(
            const TileCoordinates& origin,
            const int wanderingCredits
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const TileCoordinates& origin,
            const TileCoordinates& destination
        ) const override;
        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const DynamicElementCoordinates& origin,
            const TileCoordinates& destination
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const TileCoordinates& origin,
            const TileCoordinates& destination
        ) const override;
        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const DynamicElementCoordinates& origin,
            const TileCoordinates& destination
        ) const override;

        virtual QSharedPointer<PathInterface> generatePreferedShortestPathTo(
            const TileCoordinates& origin,
            const TileCoordinates& destination,
            bool restrictedToRoads
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestPathToClosestMatch(
            const TileCoordinates& origin,
            std::function<bool(const TileCoordinates&)> match
        ) const override;

        QList<TileCoordinates> generateShortestPathForRoad(
            const TileCoordinates& origin,
            const TileCoordinates& destination
        ) const;
};

#endif // PATHGENERATOR_HPP
