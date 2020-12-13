#ifndef PATHGENERATORINTERFACE_HPP
#define PATHGENERATORINTERFACE_HPP

#include <functional>
#include <QtCore/QSharedPointer>

class MapCoordinates;
class PathInterface;

using MapCoordinatesMatcher = std::function<bool(const MapCoordinates&)>;

class PathGeneratorInterface
{
    public:
        virtual ~PathGeneratorInterface() {};

        /**
         * @brief Generate a path for a wandering character.
         */
        virtual QSharedPointer<PathInterface> generateWanderingPath(
            const MapCoordinates& origin,
            const int wanderingCredits
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to target.
         */
        virtual QSharedPointer<PathInterface> generateShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to target by using roads only.
         */
        virtual QSharedPointer<PathInterface> generateShortestRoadPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to targe, prefering roads if available.
         *
         * If the `restrictedToRoads` attribute is `true` and no road path is found, then no path will be returned.
         */
        virtual QSharedPointer<PathInterface> generatePreferedShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination,
            bool restrictedToRoads
        ) const = 0;

        /**
         * @brief Generate shortest path to the closest location matching the given `match` criteria.
         */
        virtual QSharedPointer<PathInterface> generateShortestPathToClosestMatch(
            const MapCoordinates& origin,
            MapCoordinatesMatcher match
        ) const = 0;
};

#endif // PATHGENERATORINTERFACE_HPP
