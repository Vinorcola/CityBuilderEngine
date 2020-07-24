#include "BuildingProcessor.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



BuildingProcessor::BuildingProcessor(QObject* parent) :
    QObject(parent),
    AbstractProcessable(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void BuildingProcessor::registerBuilding(AbstractProcessableStaticMapElement* building)
{
    waitingForRegistrationList.append(building);
}



void BuildingProcessor::unregisterBuilding(AbstractProcessableStaticMapElement* building)
{
    waitingForUnregistrationList.append(building);
}



void BuildingProcessor::process(const CycleDate& date)
{
    // Process current processable list.
    for (auto processable: processableList) {
        if (processable) {
            processable->process(date);
        } else {
            waitingForUnregistrationList.append(processable);
        }
    }

    // Process unregistration.
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.removeOne(waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    while (!waitingForRegistrationList.isEmpty()) {
        auto processable(waitingForRegistrationList.takeFirst());
        if (processable) {
            processable->init(date);
            processableList.append(processable);
        }
    }
}
