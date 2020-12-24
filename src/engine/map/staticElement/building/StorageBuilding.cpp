#include "StorageBuilding.hpp"

#include <QtGlobal>

#include "src/engine/map/dynamicElement/character/DeliveryManCharacter.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/state/BuildingState.hpp"



StorageBuilding::StorageBuilding(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) :
    AbstractStoringBuilding(conf, area, orientation, entryPointTile),
    stock()
{

}



QSharedPointer<AbstractStoringBuilding> StorageBuilding::Create(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    auto storage(new StorageBuilding(conf, area, orientation, entryPointTile));
    QSharedPointer<AbstractStoringBuilding> pointer(storage);
    storage->selfReference = pointer;

    return pointer;
}



bool StorageBuilding::require(const ItemInformation& /*itemConf*/) const
{
    return false;
}



int StorageBuilding::storableQuantity(const ItemInformation& /*itemConf*/) const
{
    int currentStoredQuantity(0);
    for (auto itemQuantity : stock) {
        currentStoredQuantity += itemQuantity;
    }

    return conf.getStorageConf().maxQuantity - currentStoredQuantity;
}



void StorageBuilding::process(const CycleDate& /*date*/)
{

}



bool StorageBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    auto deliveryMan(dynamic_cast<DeliveryManCharacter*>(&actor));
    if (deliveryMan) {
        auto& item(deliveryMan->getTransportedItemConf());
        auto quantity(qMin(storableQuantity(item), deliveryMan->getTransportedQuantity()));
        if (quantity > 0) {
            deliveryMan->unload(quantity);
            store(item, quantity);

            return true;
        }
    }

    return false;
}



BuildingState StorageBuilding::getCurrentState() const
{
    return BuildingState::CreateStorageState(
        reinterpret_cast<qintptr>(this),
        conf,
        area,
        orientation,
        getCurrentStatus(),
        getCurrentWorkerQuantity(),
        stateVersion,
        stock
    );
}



void StorageBuilding::store(const ItemInformation& itemConf, const int quantity)
{
    stock[&itemConf] += quantity;
}
