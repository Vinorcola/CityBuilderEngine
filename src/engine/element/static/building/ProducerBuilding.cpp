#include "ProducerBuilding.hpp"



ProducerBuilding::ProducerBuilding(
    QObject* parent,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    rawMaterialStock(0)
{

}



void ProducerBuilding::process(const CycleDate& date)
{

}
