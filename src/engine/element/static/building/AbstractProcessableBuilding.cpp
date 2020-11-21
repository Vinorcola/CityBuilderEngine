#include "AbstractProcessableBuilding.hpp"



AbstractProcessableBuilding::AbstractProcessableBuilding(
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
):
    AbstractBuilding(conf, area),
    entryPoint(entryPoint),
    selfReference(nullptr)
{

}



QWeakPointer<AbstractProcessableBuilding> AbstractProcessableBuilding::getSelfReference() const
{
    return selfReference;
}



const MapCoordinates& AbstractProcessableBuilding::getEntryPoint() const
{
    return entryPoint;
}



bool AbstractProcessableBuilding::processInteraction(const CycleDate& /*date*/, Character& /*actor*/)
{
    return false;
}
