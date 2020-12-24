#include "IndustrialBuilding.hpp"

#include "src/engine/map/dynamicElement/character/DeliveryManCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/ItemInformation.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"



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

    if (productionCountDown > 0) {
        // On-going production.
        productionCountDown -= getCurrentWorkerQuantity();
        notifyViewDataChange();
        if (productionCountDown <= 0) {
            handleProduction();
        }
        return;
    }

    if (rawMaterialStock >= conf.getIndustrialConf().requiredQuantityForProduction) {
        // Production is ready, but delivery man was outside.
        handleProduction();
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
    characterGenerator(characterGenerator),
    rawMaterialStock(0),
    deliveryMan(),
    productionCountDown(conf.getIndustrialConf().productionInterval * conf.getMaxWorkers())
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
        productionCountDown = conf.getIndustrialConf().productionInterval * conf.getMaxWorkers();
        notifyViewDataChange();
    }
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
