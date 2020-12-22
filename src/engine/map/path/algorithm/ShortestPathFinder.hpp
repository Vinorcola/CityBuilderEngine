#ifndef SHORTESTPATHFINDER_HPP
#define SHORTESTPATHFINDER_HPP

#include <QtCore/QList>

class Tile;

/**
 * @brief An A* algorithm executor for finding the shortest path between a current location and a destination.
 */
class ShortestPathFinder
{
    public:
        static QList<const Tile*> getShortestPath(
            const Tile& origin,
            const Tile& destination,
            const bool restrictedToRoads
        );
        static QList<const Tile*> getShortestRoadablePath(const Tile& origin, const Tile& destination);
};

#endif // SHORTESTPATHFINDER_HPP
