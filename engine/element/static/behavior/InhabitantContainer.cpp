#include "InhabitantContainer.hpp"

const int INHABITANTS_PER_IMMIGRANT(4);



InhabitantContainer::InhabitantContainer(AbstractProcessableStaticMapElement* issuer) :
    AbstractStaticElementBehavior(issuer),
    issuer(issuer),
    housingCapacity(8),
    inhabitants(0),
    currentImmigrant()
{

}



void InhabitantContainer::init(const CycleDate& /*date*/)
{
    emit freeCapacityChanged(0, housingCapacity, issuer, [this](TargetedWalker* immigrant) {
        currentImmigrant = immigrant;
    });
}



void InhabitantContainer::process(const CycleDate& /*date*/)
{

}



bool InhabitantContainer::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* actor)
{
    if (actor == currentImmigrant) {
        emit requestDynamicElementDestruction(currentImmigrant, [this]() {
            currentImmigrant.clear();
            auto previousHousingCapacity(housingCapacity);
            inhabitants += INHABITANTS_PER_IMMIGRANT;
            if (inhabitants > housingCapacity) {
                emit inhabitantsChanged(INHABITANTS_PER_IMMIGRANT - (inhabitants - housingCapacity));
                inhabitants = housingCapacity;
            } else {
                emit inhabitantsChanged(INHABITANTS_PER_IMMIGRANT);
            }
            if (inhabitants < housingCapacity) {
                emit freeCapacityChanged(previousHousingCapacity, housingCapacity - inhabitants, issuer, [this](TargetedWalker* immigrant) {
                    currentImmigrant = immigrant;
                });
            }
        });

        return true;
    }

    return false;
}



void InhabitantContainer::setActivitySpeedRatio(qreal /*ratio*/, const CycleDate& /*currentDate*/)
{
    // This behavior does not have any activity.
}
