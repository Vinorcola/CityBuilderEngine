#include "RoadLocationCache.hpp"

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



QString RoadLocationCache::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
