#include "LaboratoryBuilding.hpp"



LaboratoryBuilding::LaboratoryBuilding(
    QObject* parent,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint)
{

}



void LaboratoryBuilding::process(const CycleDate& date)
{

}
