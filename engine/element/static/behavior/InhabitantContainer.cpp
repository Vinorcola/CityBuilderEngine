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
    emit freeCapacityChanged(0, housingCapacity, [this](AbstractDynamicMapElement* immigrant) {
        static_cast<TargetedWalker*>(immigrant)->assignTarget(issuer);
        currentImmigrant = static_cast<TargetedWalker*>(immigrant);
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
                emit freeCapacityChanged(previousHousingCapacity, housingCapacity - inhabitants, [this](AbstractDynamicMapElement* immigrant) {
                    static_cast<TargetedWalker*>(immigrant)->assignTarget(issuer);
                    currentImmigrant = static_cast<TargetedWalker*>(immigrant);
                });
            }
        });

        return true;
    }

    return false;
}
