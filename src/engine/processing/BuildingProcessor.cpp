#include "BuildingProcessor.hpp"

#include "src/engine/processing/CycleDate.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"
#include "src/defines.hpp"



BuildingProcessor::BuildingProcessor(AbstractProcessable& workerHandler) :
    AbstractProcessable(),
    workerHandler(workerHandler),
    entryPointList(),
    buildingList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void BuildingProcessor::registerMapEntryPoint(const QSharedPointer<AbstractProcessable>& entryPoint)
{
    entryPointList.append(entryPoint);
}



void BuildingProcessor::registerBuilding(const QSharedPointer<AbstractProcessable>& building)
{
    waitingForRegistrationList.append(building);
}



void BuildingProcessor::unregisterBuilding(const QSharedPointer<AbstractProcessable>& building)
{
    waitingForUnregistrationList.append(building.get());
}



void BuildingProcessor::process(const CycleDate& date)
{
    // Process mep entry points.
    for (auto& entryPointRef : entryPointList) {
        auto entryPoint(entryPointRef.toStrongRef());
        if (entryPoint) {
            entryPoint->process(date);
        }
    }

    // Other buildings are processed only on a building time cycle.
    if (!date.isBuildingCycle()) {
        return;
    }

    // Process current processable list.
    for (auto& buildingRef : buildingList) {
        auto building(buildingRef.toStrongRef());
        if (building) {
            building->process(date);
        }
    }

    // Process unregistration.
    cleanInvalids(buildingList);
    while (!waitingForUnregistrationList.isEmpty()) {
        buildingList.remove(waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    for (auto& newProcessable : waitingForRegistrationList) {
        buildingList.insert(newProcessable.get(), newProcessable);
    }
    waitingForRegistrationList.clear();

    // Worker handler is process at the end.
    workerHandler.process(date);
}
