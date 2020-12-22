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
    AbstractProcessableBuilding(conf, area, orientation, entryPointTile),
    stock()
{

}



QSharedPointer<StorageBuilding> StorageBuilding::Create(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    auto storage(new StorageBuilding(conf, area, orientation, entryPointTile));
    QSharedPointer<StorageBuilding> pointer(storage);
    storage->selfReference = pointer;

    return pointer;
}



int StorageBuilding::storableQuantity(const ItemInformation& /*itemConf*/, const int maxQuantity) const
{
    int currentStoredQuantity(0);
    for (auto itemQuantity : stock) {
        currentStoredQuantity += itemQuantity;
    }

    return qMin(conf.getStorageConf().maxQuantity - currentStoredQuantity, maxQuantity);
}



void StorageBuilding::process(const CycleDate& /*date*/)
{

}



bool StorageBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    auto deliveryCharacter(dynamic_cast<DeliveryManCharacter*>(&actor));
    if (deliveryCharacter) {
        auto& item(deliveryCharacter->getTransportedItemConf());
        auto quantity(storableQuantity(item, deliveryCharacter->getTransportedQuantity()));
        if (quantity > 0) {
            deliveryCharacter->unload(quantity);
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
