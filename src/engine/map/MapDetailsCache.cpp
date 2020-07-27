#include "MapDetailsCache.hpp"

#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/exceptions/NotImplementedException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



MapDetailsCache::MapDetailsCache() :
    nonTraversableCoordinates(),
    nonConstructibleCoordinates(),
    roadCoordinates()
{

}



void MapDetailsCache::registerBuildingConstruction(const BuildingInformation& conf, const MapArea& area)
{
    switch (conf.getType()) {
        case BuildingInformation::Type::CityEntryPoint:
        case BuildingInformation::Type::Road:
            registerRoadLocation(area.getLeft());
            break;

        default:
            registerNonTraversableAndNonConstructibleArea(area);
            break;
    }
}



void MapDetailsCache::registerNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    if (area.getSize().getValue() != 1) {
        throw NotImplementedException("Registering nature elements with size higher than 1 is not implemented in map detail cache.");
    }

    auto hash(hashCoordinates(area.getLeft()));
    nonConstructibleCoordinates << hash;
    if (!conf.isTraversable()) {
        nonTraversableCoordinates << hash;
    }
}



bool MapDetailsCache::isLocationTraversable(const MapCoordinates& location) const
{
    return !nonTraversableCoordinates.contains(hashCoordinates(location));
}



bool MapDetailsCache::isLocationConstructible(const MapCoordinates& location) const
{
    return !nonConstructibleCoordinates.contains(hashCoordinates(location));
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



void MapDetailsCache::registerRoadLocation(const MapCoordinates& location)
{
    roadCoordinates << hashCoordinates(location);
}



void MapDetailsCache::registerNonTraversableAndNonConstructibleArea(const MapArea& area)
{
    switch (area.getSize().getValue()) {
        case 1:
            registerNonTraversableAndNonConstructibleLocation(area.getLeft());
            break;

        case 2:
            registerNonTraversableAndNonConstructibleLocation(area.getLeft());
            registerNonTraversableAndNonConstructibleLocation(area.getTop());
            registerNonTraversableAndNonConstructibleLocation(area.getRight());
            registerNonTraversableAndNonConstructibleLocation(area.getBottom());
            break;

        default:
            auto left(area.getLeft());
            auto right(area.getRight());
            int xMax(right.getX());
            int yMax(right.getY());
            for (int x(left.getX()); x <= xMax; ++x) {
                for (int y(left.getY()); y <= yMax; ++y) {
                    registerNonTraversableAndNonConstructibleLocation({ x, y });
                }
            }
    }
}



void MapDetailsCache::registerNonTraversableAndNonConstructibleLocation(const MapCoordinates& location)
{
    auto hash(hashCoordinates(location));
    nonTraversableCoordinates << hash;
    nonConstructibleCoordinates << hash;
}



void MapDetailsCache::unregisterRoadLocation(const MapCoordinates& location)
{
    roadCoordinates.remove(hashCoordinates(location));
}



QString MapDetailsCache::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
