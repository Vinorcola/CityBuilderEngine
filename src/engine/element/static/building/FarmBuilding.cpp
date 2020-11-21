#include "FarmBuilding.hpp"

#include <QtGlobal>

#include "src/engine/element/dynamic/character/DeliveryManCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/state/BuildingState.hpp"
#include "src/global/conf/BuildingInformation.hpp"



FarmBuilding::FarmBuilding(
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, entryPoint),
    characterFactory(characterFactory),
    completeGrowingDate(),
    deliveryMan()
{

}



void FarmBuilding::init(const CycleDate& date)
{
    completeGrowingDate.reassign(date, CycleDate::getCyclesPerYear());
}



void FarmBuilding::process(const CycleDate& date)
{
    if (date.isFirstCycleOfMonth() && date.getMonth() == conf.getFarmConf().harvestMonth) {
        if (deliveryMan.isValid()) {
            // The delivery man is outside. We do not harvest now.
            // Next harvest will occure as soon as the growing is complete and thedelivery man is back.
            return;
        }

        harvest(date);
    }
    else if (date > completeGrowingDate) {
        // Case where the delivery man were outside at the begining of the harvest month.
        if (deliveryMan.isValid()) {
            // The delivery man is still outside. We do not harvest now.
            return;
        }

        harvest(date);
    }
}



bool FarmBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    if (deliveryMan.matches(actor)) {
        this->deliveryMan.clear();

        return true;
    }

    return false;
}



BuildingState FarmBuilding::getCurrentState() const
{
    // TODO: Calculate growth percent.
    return BuildingState::CreateFarmState(reinterpret_cast<qintptr>(this), conf, area, stateVersion, 0);
}



void FarmBuilding::harvest(const CycleDate& date)
{
    int remainingCyclesToBeComplete(completeGrowingDate - date);
    qreal productivityRatio(
        qMin(
            1.0,
            static_cast<qreal>(CycleDate::getCyclesPerYear()) /
            static_cast<qreal>(CycleDate::getCyclesPerYear() + remainingCyclesToBeComplete)
        )
    );
    int quantity(productivityRatio * conf.getFarmConf().maxQuantityHarvested);

    deliveryMan.reassign(characterFactory.generateDeliveryMan(
        conf.getFarmConf().deliveryManConf,
        *this,
        conf.getFarmConf().producedItemConf,
        quantity
    ));

    completeGrowingDate.reassign(date, CycleDate::getCyclesPerYear());
}
