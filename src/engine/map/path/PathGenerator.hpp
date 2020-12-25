#ifndef PATHGENERATOR_HPP
#define PATHGENERATOR_HPP

#include "src/engine/map/path/PathGeneratorInterface.hpp"

class Tile;

class PathGenerator : public PathGeneratorInterface
{
    public:
        virtual QSharedPointer<PathInterface> generateWanderingPath(
            const Tile& origin,
            const int wanderingCredits
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const Tile& origin,
            const Tile& destination
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const Tile& origin,
            const Tile& destination
        ) const override;

        virtual QSharedPointer<PathInterface> generatePreferedShortestPathTo(
            const Tile& origin,
            const Tile& destination,
            bool restrictedToRoads
        ) const override;

        virtual QSharedPointer<PathInterface> generateShortestPathToClosestMatch(
            const Tile& origin,
            TargetFetcher getTarget
        ) const override;

        QList<const Tile*> generateShortestPathForRoad(
            const Tile& origin,
            const Tile& destination
        ) const;
};

#endif // PATHGENERATOR_HPP
