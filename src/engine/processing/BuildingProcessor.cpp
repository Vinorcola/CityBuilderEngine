#include "BuildingProcessor.hpp"

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"



BuildingProcessor::BuildingProcessor() :
    AbstractProcessable(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void BuildingProcessor::registerBuilding(AbstractProcessableBuilding& building)
{
    waitingForRegistrationList.append(building);
}



void BuildingProcessor::unregisterBuilding(AbstractProcessableBuilding& building)
{
    waitingForUnregistrationList.append(&building);
}



void BuildingProcessor::process(const CycleDate& date)
{
    // Process current processable list.
    for (auto processable : processableList) {
        if (processable.isValid()) {
            processable.get().process(date);
        }
    }

    // Process unregistration.
    processableList.cleanAllInvalids();
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.remove(*waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    waitingForRegistrationList.moveAllContentTo(processableList);
}
