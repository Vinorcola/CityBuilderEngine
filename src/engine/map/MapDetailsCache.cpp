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
        case BuildingInformation::Type::Road: {
            auto hash(hashCoordinates(area.getLeft()));
            roadCoordinates << hash;
            nonConstructibleCoordinates << hash;
            break;
        }

        default:
            for (auto coordinates : area) {
                auto hash(hashCoordinates(coordinates));
                nonTraversableCoordinates << hash;
                nonConstructibleCoordinates << hash;
            }
            break;
    }
}



void MapDetailsCache::registerBuildingDestruction(const MapArea& area)
{
    for (auto coordinates : area) {
        auto hash(hashCoordinates(coordinates));
        roadCoordinates.remove(hash);
        nonTraversableCoordinates.remove(hash);
        nonConstructibleCoordinates.remove(hash);
    }
}



void MapDetailsCache::registerNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    for (auto coordinates : area) {
        auto hash(hashCoordinates(coordinates));
        nonConstructibleCoordinates << hash;
        if (!conf.isTraversable()) {
            nonTraversableCoordinates << hash;
        }
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



QString MapDetailsCache::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
