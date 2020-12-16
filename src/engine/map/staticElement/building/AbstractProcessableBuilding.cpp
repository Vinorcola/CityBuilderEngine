#include "AbstractProcessableBuilding.hpp"

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/state/BuildingState.hpp"



AbstractProcessableBuilding::AbstractProcessableBuilding(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const TileCoordinates& entryPoint
):
    AbstractBuilding(conf, area, orientation),
    entryPoint(entryPoint),
    currentWorkerQuantity(0),
    selfReference(nullptr)
{

}



QWeakPointer<AbstractProcessableBuilding> AbstractProcessableBuilding::getSelfReference() const
{
    return selfReference;
}



const TileCoordinates& AbstractProcessableBuilding::getEntryPoint() const
{
    return entryPoint;
}



bool AbstractProcessableBuilding::isActive() const
{
    return getConf().getMaxWorkers() == 0 || currentWorkerQuantity > 0;
}



void AbstractProcessableBuilding::assignWorkers(int workerQuantity)
{
    if (workerQuantity != currentWorkerQuantity) {
        currentWorkerQuantity = workerQuantity;
        notifyViewDataChange();
    }
}



bool AbstractProcessableBuilding::processInteraction(const CycleDate& /*date*/, Character& /*actor*/)
{
    return false;
}



BuildingState AbstractProcessableBuilding::getCurrentState() const
{
    return {
        reinterpret_cast<qintptr>(this),
        conf,
        area,
        orientation,
        getCurrentStatus(),
        currentWorkerQuantity,
        stateVersion,
    };
}



int AbstractProcessableBuilding::getCurrentWorkerQuantity() const
{
    return currentWorkerQuantity;
}



BuildingStatus AbstractProcessableBuilding::getCurrentStatus() const
{
    return isActive() ? BuildingStatus::Active : BuildingStatus::Inactive;
}
