#include "BuildingProcessor.hpp"

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"



BuildingProcessor::BuildingProcessor(AbstractProcessable& populationHandler) :
    AbstractProcessable(),
    populationHandler(populationHandler),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void BuildingProcessor::registerBuilding(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    waitingForRegistrationList.append(building);
}



void BuildingProcessor::unregisterBuilding(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    waitingForUnregistrationList.append(building.get());
}



void BuildingProcessor::init(const CycleDate& date)
{
    populationHandler.init(date);
}



void BuildingProcessor::process(const CycleDate& date)
{
    // Process current processable list.
    for (auto& processableRef : processableList) {
        auto processable(processableRef.toStrongRef());
        if (processable) {
            processable->process(date);
        }
    }

    // Process unregistration.
    cleanInvalids(processableList);
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.remove(waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    for (auto& newProcessable : waitingForRegistrationList) {
        newProcessable->init(date);
        processableList.insert(newProcessable.get(), newProcessable);
    }
    waitingForRegistrationList.clear();

    populationHandler.process(date);
}
