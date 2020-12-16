#ifndef SHORTESTPATHFINDER_HPP
#define SHORTESTPATHFINDER_HPP

#include <QtCore/QList>

class MapDetailsInterface;
class TileCoordinates;

/**
 * @brief An A* algorithm executor for finding the shortest path between a current location and a destination.
 */
class ShortestPathFinder
{
    private:
        const MapDetailsInterface& mapDetails;

    public:
        explicit ShortestPathFinder(const MapDetailsInterface& mapDetails);

        QList<TileCoordinates> getShortestPath(
            const TileCoordinates& origin,
            const TileCoordinates& destination,
            const bool restrictedToRoads
        ) const;

        QList<TileCoordinates> getShortestRoadablePath(
            const TileCoordinates& origin,
            const TileCoordinates& destination
        ) const;
};

#endif // SHORTESTPATHFINDER_HPP
