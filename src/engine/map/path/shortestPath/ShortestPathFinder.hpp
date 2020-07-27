#ifndef SHORTESTPATHFINDER_HPP
#define SHORTESTPATHFINDER_HPP

#include <QtCore/QList>

class MapCoordinates;
class MapDetailsInterface;

/**
 * @brief An A* algorithm executor for finding the shortest path between a current location and a destination.
 */
class ShortestPathFinder
{
    private:
        const MapDetailsInterface& mapDetails;

    public:
        explicit ShortestPathFinder(const MapDetailsInterface& mapDetails);

        QList<MapCoordinates> getShortestPath(
            const MapCoordinates& origin,
            const MapCoordinates& destination,
            const bool restrictedToRoads
        ) const;
};

#endif // SHORTESTPATHFINDER_HPP
