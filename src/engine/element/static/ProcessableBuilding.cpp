#include "ProcessableBuilding.hpp"



ProcessableBuilding::ProcessableBuilding(
        QObject* parent,
        const BuildingInformation* conf,
        const MapArea& area,
        const MapCoordinates& entryPoint
):
    Building(parent, conf, area),
    entryPoint(entryPoint)
{

}



const MapCoordinates& ProcessableBuilding::getEntryPoint() const
{
    return entryPoint;
}
