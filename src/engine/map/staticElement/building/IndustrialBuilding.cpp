#include "IndustrialBuilding.hpp"

#include "src/engine/map/dynamicElement/character/DeliveryManCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/ItemInformation.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"
#include "src/global/state/BuildingState.hpp"



QSharedPointer<AbstractStoringBuilding> IndustrialBuilding::Create(
    CharacterGeneratorInterface& characterGenerator,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    auto industrial(new IndustrialBuilding(characterGenerator, conf, area, orientation, entryPointTile));
    QSharedPointer<AbstractStoringBuilding> pointer(industrial);
    industrial->selfReference = pointer;

    return pointer;
}



bool IndustrialBuilding::require(const ItemInformation& itemConf) const
{
    if (itemConf != conf.getIndustrialConf().rawMaterialConf) {
        return false;
    }

    return rawMaterialStock < conf.getIndustrialConf().maxRawMaterialStock;
}



int IndustrialBuilding::storableQuantity(const ItemInformation& itemConf) const
{
    if (itemConf != conf.getIndustrialConf().rawMaterialConf) {
        return 0;
    }

    return conf.getIndustrialConf().maxRawMaterialStock - rawMaterialStock;
}



void IndustrialBuilding::process(const CycleDate& /*date*/)
{
    if (!isActive()) {
        return;
    }

    if (rawMaterialStock >= conf.getIndustrialConf().requiredQuantityForProduction) {
        if (productionCountDown > 0) {
            productionCountDown -= getCurrentWorkerQuantity();
            notifyViewDataChange();
        }
        if (productionCountDown <= 0) {
            handleProduction();
        }
    }
}



bool IndustrialBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    if (matches(deliveryMan, actor)) {
        deliveryMan.clear();

        return true;
    }

    auto deliveryMan(dynamic_cast<DeliveryManCharacter*>(&actor));
    if (deliveryMan) {
        auto& item(deliveryMan->getTransportedItemConf());
        if (item != conf.getIndustrialConf().rawMaterialConf) {
            return false;
        }
        auto quantity(qMin(storableQuantity(item), deliveryMan->getTransportedQuantity()));
        if (quantity > 0) {
            deliveryMan->unload(quantity);
            rawMaterialStock += quantity;

            return true;
        }
    }

    return false;
}



IndustrialBuilding::IndustrialBuilding(
    CharacterGeneratorInterface& characterGenerator,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) :
    AbstractStoringBuilding(conf, area, orientation, entryPointTile),
    PRODUCTION_INTERVAL(conf.getIndustrialConf().productionInterval * conf.getMaxWorkers()),
    characterGenerator(characterGenerator),
    rawMaterialStock(0),
    deliveryMan(),
    productionCountDown(PRODUCTION_INTERVAL)
{

}



void IndustrialBuilding::handleProduction()
{
    if (!deliveryMan) {
        deliveryMan = characterGenerator.generateDeliveryMan(
            conf.getIndustrialConf().deliveryManConf,
            selfReference,
            conf.getIndustrialConf().producedItemConf,
            1
        );
        rawMaterialStock -= conf.getIndustrialConf().requiredQuantityForProduction;
        productionCountDown = PRODUCTION_INTERVAL;
        notifyViewDataChange();
    }
}



BuildingState IndustrialBuilding::getCurrentState() const
{
    return BuildingState::CreateIndustrialState(
        reinterpret_cast<qintptr>(this),
        conf,
        area,
        orientation,
        getCurrentStatus(),
        getCurrentWorkerQuantity(),
        stateVersion,
        rawMaterialStock,
        static_cast<int>(
            100.0 *
            static_cast<qreal>(PRODUCTION_INTERVAL - productionCountDown) / static_cast<qreal>(PRODUCTION_INTERVAL)
        )
    );
}



BuildingStatus IndustrialBuilding::getCurrentStatus() const
{
    if (!isActive()) {
        return BuildingStatus::Inactive;
    }
    if (rawMaterialStock > 0) {
        return BuildingStatus::Working;
    }

    return BuildingStatus::Active;
}
