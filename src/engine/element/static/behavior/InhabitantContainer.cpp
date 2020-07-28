#include "InhabitantContainer.hpp"

const int INHABITANTS_PER_IMMIGRANT(4);



InhabitantContainer::InhabitantContainer(ProcessableBuilding* issuer) :
    AbstractBehavior(issuer),
    issuer(issuer),
    housingCapacity(8),
    inhabitants(0),
    currentImmigrant()
{

}



void InhabitantContainer::init(const CycleDate& /*date*/)
{
    // TODO: Disable for now. To review.
//    emit freeCapacityChanged(0, housingCapacity, [this](Character* immigrant) {
//        immigrant->assignTarget(issuer);
//        currentImmigrant = immigrant;
//    });
}



void InhabitantContainer::process(const CycleDate& /*date*/)
{

}



bool InhabitantContainer::processInteraction(const CycleDate& /*date*/, Character* actor)
{
    if (actor == currentImmigrant) {
        currentImmigrant.clear();
        emit requestDynamicElementDestruction(actor, [this]() {
            auto previousHousingCapacity(housingCapacity);
            inhabitants += INHABITANTS_PER_IMMIGRANT;
            if (inhabitants > housingCapacity) {
                emit inhabitantsChanged(INHABITANTS_PER_IMMIGRANT - (inhabitants - housingCapacity));
                inhabitants = housingCapacity;
            } else {
                emit inhabitantsChanged(INHABITANTS_PER_IMMIGRANT);
            }
            if (inhabitants < housingCapacity) {
                emit freeCapacityChanged(previousHousingCapacity, housingCapacity - inhabitants, [this](Character* immigrant) {
                    immigrant->assignTarget(issuer);
                    currentImmigrant = immigrant;
                });
            }
        });

        return true;
    }

    return false;
}
