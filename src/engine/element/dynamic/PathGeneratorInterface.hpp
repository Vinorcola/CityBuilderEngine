#ifndef PATHGENERATORINTERFACE_HPP
#define PATHGENERATORINTERFACE_HPP

#include <functional>

#include "src/defines.hpp"

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
        virtual optional<owner<PathInterface*>> generateWanderingPath(
            const MapCoordinates& origin,
            const int wanderingCredits
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to target.
         */
        virtual optional<owner<PathInterface*>> generateShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to target by using roads only.
         */
        virtual optional<owner<PathInterface*>> generateShortestRoadPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const = 0;

        /**
         * @brief Generate the shortest path from origin to targe, prefering roads if available.
         *
         * If the `restrictedToRoads` attribute is `true` and no road path is found, then no path will be returned.
         */
        virtual optional<owner<PathInterface*>> generatePreferedShortestPathTo(
            const MapCoordinates& origin,
            const MapCoordinates& destination,
            bool restrictedToRoads
        ) const = 0;

        /**
         * @brief Generate shortest path to the closest location matching the given `match` criteria.
         */
        virtual optional<owner<PathInterface*>> generateShortestPathToClosestMatch(
            const MapCoordinates& origin,
            MapCoordinatesMatcher match
        ) const = 0;
};

#endif // PATHGENERATORINTERFACE_HPP
