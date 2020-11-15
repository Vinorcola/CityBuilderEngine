#include "AbstractProcessableBuilding.hpp"



AbstractProcessableBuilding::AbstractProcessableBuilding(
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
):
    AbstractBuilding(conf, area),
    entryPoint(entryPoint)
{

}



const MapCoordinates& AbstractProcessableBuilding::getEntryPoint() const
{
    return entryPoint;
}



bool AbstractProcessableBuilding::processInteraction(const CycleDate& /*date*/, Character& /*actor*/)
{
    return false;
}
