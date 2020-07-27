#include "MapDetailsCache.hpp"

#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/exceptions/NotImplementedException.hpp"



MapDetailsCache::MapDetailsCache() :
    nonTraversableCoordinates()
{

}



void MapDetailsCache::registerNonTraversableLocation(const MapCoordinates& location)
{
    nonTraversableCoordinates << hashCoordinates(location);
}



void MapDetailsCache::registerNonTraversableArea(const MapArea& area)
{
    switch (area.getSize().getValue()) {
        case 1:
            registerNonTraversableLocation(area.getLeft());
            break;

        case 2:
            registerNonTraversableLocation(area.getTop());
            registerNonTraversableLocation(area.getRight());
            registerNonTraversableLocation(area.getBottom());
            registerNonTraversableLocation(area.getLeft());
            break;

        default:
            auto left(area.getLeft());
            auto right(area.getRight());
            int xMax(right.getX());
            int yMax(right.getY());
            for (int x(left.getX()); x <= xMax; ++x) {
                for (int y(left.getY()); y <= yMax; ++y) {
                    registerNonTraversableLocation(MapCoordinates(x, y));
                }
            }
    }
}



bool MapDetailsCache::isLocationTraversable(const MapCoordinates& location) const
{
    return !nonTraversableCoordinates.contains(hashCoordinates(location));
}



void MapDetailsCache::registerRoadLocation(const MapCoordinates& location)
{
    roadCoordinates << hashCoordinates(location);
}



void MapDetailsCache::unregisterRoadLocation(const MapCoordinates& location)
{
    roadCoordinates.remove(hashCoordinates(location));
}



bool MapDetailsCache::hasRoadAtLocation(const MapCoordinates& location) const
{
    return roadCoordinates.contains(hashCoordinates(location));
}



MapCoordinates MapDetailsCache::getBestEntryPointForArea(const MapArea& area) const
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



QString MapDetailsCache::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
