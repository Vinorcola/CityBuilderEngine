#include "BuildingProcessor.hpp"

#include "src/engine/element/static/building/ProcessableBuilding.hpp"



BuildingProcessor::BuildingProcessor(QObject* parent) :
    QObject(parent),
    AbstractProcessable(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void BuildingProcessor::registerBuilding(ProcessableBuilding& building)
{
    waitingForRegistrationList.append(&building);
}



void BuildingProcessor::unregisterBuilding(ProcessableBuilding* building)
{
    waitingForUnregistrationList.append(building);
}



void BuildingProcessor::process(const CycleDate& date)
{
    // Process current processable list.
    for (auto processable : processableList) {
        if (processable) {
            processable->process(date);
        } else {
            waitingForUnregistrationList.append(processable);
        }
    }

    // Process unregistration.
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.remove(waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    while (!waitingForRegistrationList.isEmpty()) {
        auto processable(waitingForRegistrationList.takeFirst());
        if (processable) {
            processable->init(date);
            processableList.push_back(processable);
        }
    }
}
