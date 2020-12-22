#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <QtCore/QList>

class Tile;

using TileMatcher = std::function<bool(const Tile&)>;

/**
 * @brief An A* algorithm executor for finding the shortest path between a current location and a destination.
 */
class PathFinder
{
    public:
        /**
         * Get the shortest path for a dynamic element from an origin to a destination.
         */
        static QList<const Tile*> getShortestPath(
            const Tile& origin,
            const Tile& destination,
            const bool restrictedToRoads
        );

        /**
         * Get the shortest path where roads could be built.
         */
        static QList<const Tile*> getShortestRoadablePath(const Tile& origin, const Tile& destination);

        /**
         * Get the shortest path to the closest element that match to given requirement.
         *
         * This algorithm does not know the destination yet. It will discover the map until it find an element matching
         * the requirement (the `match` parameter) and return the shortest path to that element.
         *
         * Note that the matching element may no be traversable. In that case, the path will stop at the tile just
         * before the element. Otherwise, the path will go to the element's tile itself.
         */
        static QList<const Tile*> getShortestPathToClosestMatch(const Tile& origin, TileMatcher match);
};

#endif // PATHFINDER_HPP
