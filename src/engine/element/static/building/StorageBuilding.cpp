#include "StorageBuilding.hpp"

#include <QtGlobal>

#include "src/engine/element/dynamic/character/DeliveryManCharacter.hpp"
#include "src/engine/state/BuildingState.hpp"
#include "src/global/conf/BuildingInformation.hpp"



StorageBuilding::StorageBuilding(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPoint),
    stock()
{

}



QSharedPointer<StorageBuilding> StorageBuilding::Create(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    auto storage(new StorageBuilding(conf, area, orientation, entryPoint));
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
