#include "HousingBuilding.hpp"

const int INHABITANTS_PER_IMMIGRANT(4);



HousingBuilding::HousingBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableStaticMapElement(parent, conf, area, entryPoint),
    housingCapacity(8),
    inhabitants(0),
    currentImmigrant()
{

}



void HousingBuilding::init(const CycleDate& /*date*/)
{
    emit freeCapacityChanged(0, housingCapacity, [this](TargetedWalker* immigrant) {
        currentImmigrant = immigrant;
    });
}



void HousingBuilding::process(const CycleDate& /*date*/)
{

}



bool HousingBuilding::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* actor)
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
                emit freeCapacityChanged(previousHousingCapacity, housingCapacity - inhabitants, [this](TargetedWalker* immigrant) {
                    currentImmigrant = immigrant;
                });
            }
        });

        return true;
    }

    return false;
}
