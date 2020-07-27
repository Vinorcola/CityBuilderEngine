#include "RoadLocationCache.hpp"

#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"



RoadLocationCache::RoadLocationCache() :
    roadCoordinates()
{

}



void RoadLocationCache::registerRoadLocation(const MapCoordinates& location)
{
    roadCoordinates << hashCoordinates(location);
}



void RoadLocationCache::unregisterRoadLocation(const MapCoordinates& location)
{
    roadCoordinates.remove(hashCoordinates(location));
}



bool RoadLocationCache::hasRoadAtLocation(const MapCoordinates& location) const
{
    return roadCoordinates.contains(hashCoordinates(location));
}



MapCoordinates RoadLocationCache::getBestEntryPointForArea(const MapArea& area) const
{
    // Fetch a location arround the area, starting at the coordinates at north of left point, and turning clockwise
    // arround the area.

    auto left(area.getLeft());
    auto right(area.getRight());
    int moveX(1);
    int moveY(0);

    MapCoordinates coordinates(left.getNorth());
    while (!hasRoadAtLocation(coordinates)) {
        coordinates.setX(coordinates.getX() + moveX);
        coordinates.setY(coordinates.getY() + moveY);

        if (moveX == 1 && coordinates.getX() > right.getX()) {
            // Overstep top corner.
            moveX = 0;
            moveY = 1;
        }
        else if (moveY == 1 && coordinates.getY() > right.getY()) {
            // Overstep right corner.
            moveX = -1;
            moveY = 0;
        }
        else if (moveX == -1 && coordinates.getX() < left.getX()) {
            // Overstep bottom corner.
            moveY = -1;
            moveX = 0;
        }
        else if (moveY == -1 && coordinates.getY() < left.getY()) {
            // Overstep left corner. No node found.
            return MapCoordinates();
        }
    }

    return coordinates;
}



QString RoadLocationCache::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
