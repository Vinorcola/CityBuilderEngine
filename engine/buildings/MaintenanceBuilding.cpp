#include "MaintenanceBuilding.hpp"





MaintenanceBuilding::MaintenanceBuilding(const MapCoordinates& leftCoordinates) :
    AbstractBuilding(MapArea(leftCoordinates, MapSize(2)), 5)
{
    
}
