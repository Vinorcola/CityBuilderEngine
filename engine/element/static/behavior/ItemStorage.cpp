#include "ItemStorage.hpp"

#include "engine/element/static/ProcessableBuilding.hpp"
#include "global/conf/BehaviorInformation.hpp"
#include "global/conf/ItemInformation.hpp"



ItemStorage::ItemStorage(ProcessableBuilding* issuer, const BehaviorInformation* behaviorInformation) :
    AbstractBehavior(issuer),
    issuer(issuer),
    availableItems(behaviorInformation->getItems()),
    storage()
{
    for (auto availableItem : availableItems) {
        storage.insert(availableItem->getKey(), new ItemStatus());
    }
}



ItemStorage::~ItemStorage()
{
    qDeleteAll(storage);
}



void ItemStorage::init(const CycleDate& date)
{

}



void ItemStorage::process(const CycleDate& date)
{

}



bool ItemStorage::processInteraction(const CycleDate& date, Character* actor)
{
    return false;
}
