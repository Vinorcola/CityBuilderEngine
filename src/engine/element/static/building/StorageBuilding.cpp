#include "StorageBuilding.hpp"



StorageBuilding::StorageBuilding(
    QObject* parent,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    stock()
{

}



void StorageBuilding::process(const CycleDate& /*date*/)
{

}
