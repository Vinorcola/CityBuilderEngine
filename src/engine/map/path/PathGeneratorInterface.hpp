#ifndef PATHGENERATORINTERFACE_HPP
#define PATHGENERATORINTERFACE_HPP

#include <functional>
#include <QtCore/QSharedPointer>

class DynamicElementCoordinates;
class PathInterface;
class TileCoordinates;

using TileCoordinatesMatcher = std::function<bool(const TileCoordinates&)>;

class PathGeneratorInterface
{
    public:
        virtual ~PathGeneratorInterface() {};

        /**
         * @brief Generate a path for a wandering character.
         */
        virtual QSharedPointer<PathInterface> generateWanderingPath(
            const TileCoordinates& origin,
            const int wanderingCredits
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to target.
         */
        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const TileCoordinates& origin,
            const TileCoordinates& destination
        ) const = 0;
        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const DynamicElementCoordinates& origin,
            const TileCoordinates& destination
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to target by using roads only.
         */
        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const TileCoordinates& origin,
            const TileCoordinates& destination
        ) const = 0;
        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const DynamicElementCoordinates& origin,
            const TileCoordinates& destination
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to targe, prefering roads if available.
         *
         * If the `restrictedToRoads` attribute is `true` and no road path is found, then no path will be returned.
         */
        virtual QSharedPointer<PathInterface> generatePreferedShortestPathTo(
            const TileCoordinates& origin,
            const TileCoordinates& destination,
            bool restrictedToRoads
        ) const = 0;

        /**
         * @brief Generate shortest path to the closest location matching the given `match` criteria.
         */
        virtual QSharedPointer<PathInterface> generateShortestPathToClosestMatch(
            const TileCoordinates& origin,
            TileCoordinatesMatcher match
        ) const = 0;
};

#endif // PATHGENERATORINTERFACE_HPP
