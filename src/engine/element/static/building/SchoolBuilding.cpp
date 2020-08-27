#include "SchoolBuilding.hpp"



SchoolBuilding::SchoolBuilding(
    QObject* parent,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint)
{

}



void SchoolBuilding::process(const CycleDate& date)
{

}
