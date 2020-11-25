#include "AbstractProcessableBuilding.hpp"

#include "src/engine/state/BuildingState.hpp"
#include "src/global/conf/BuildingInformation.hpp"



AbstractProcessableBuilding::AbstractProcessableBuilding(
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
):
    AbstractBuilding(conf, area),
    entryPoint(entryPoint),
    currentWorkerQuantity(0),
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
        isActive() ? BuildingState::Status::Active : BuildingState::Status::Inactive,
        currentWorkerQuantity,
        stateVersion,
    };
}



int AbstractProcessableBuilding::getCurrentWorkerQuantity() const
{
    return currentWorkerQuantity;
}



bool AbstractProcessableBuilding::isActive() const
{
    return getConf().getMaxWorkers() == 0 || currentWorkerQuantity > 0;
}
