#include "TraversableLocationCache.hpp"

#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/exceptions/NotImplementedException.hpp"



TraversableLocationCache::TraversableLocationCache() :
    nonTraversableCoordinates()
{

}



void TraversableLocationCache::registerNonTraversableLocation(const MapCoordinates& location)
{
    nonTraversableCoordinates << hashCoordinates(location);
}



void TraversableLocationCache::registerNonTraversableArea(const MapArea& area)
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



bool TraversableLocationCache::isLocationTraversable(const MapCoordinates& location) const
{
    return !nonTraversableCoordinates.contains(hashCoordinates(location));
}



QString TraversableLocationCache::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
