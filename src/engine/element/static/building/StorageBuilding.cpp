#include "StorageBuilding.hpp"

#include <QtGlobal>

#include "src/engine/element/dynamic/character/DeliveryCharacter.hpp"
#include "src/global/conf/BuildingInformation.hpp"



StorageBuilding::StorageBuilding(
    QObject* parent,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    stock()
{

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
    auto deliveryCharacter(dynamic_cast<DeliveryCharacter*>(&actor));
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



void StorageBuilding::store(const ItemInformation& itemConf, const int quantity)
{
    stock[&itemConf] += quantity;
}
