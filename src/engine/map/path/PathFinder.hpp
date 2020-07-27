#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <QtCore/QList>

class MapCoordinates;
class MapDetailsInterface;

/**
 * @brief An A* algorithm executor for finding the shortest path between a current location and a destination.
 */
class PathFinder
{
    private:
        const MapDetailsInterface& mapDetails;

    public:
        explicit PathFinder(const MapDetailsInterface& mapDetails);

        QList<MapCoordinates> getShortestPath(
            const MapCoordinates& origin,
            const MapCoordinates& destination,
            const bool restrictedToRoads = true
        ) const;
};

#endif // PATHFINDER_HPP
