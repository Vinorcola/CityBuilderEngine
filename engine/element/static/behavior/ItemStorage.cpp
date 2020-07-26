#include "ItemStorage.hpp"

#include <assert.h>

#include "engine/element/static/ProcessableBuilding.hpp"
#include "global/conf/BehaviorInformation.hpp"
#include "global/conf/ItemInformation.hpp"



ItemStorage::ItemStorage(ProcessableBuilding* issuer, const BehaviorInformation* behaviorInformation) :
    AbstractActivityBehavior(issuer),
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



void ItemStorage::setActivitySpeedRatio(qreal ratio, const CycleDate& /*currentDate*/)
{
    assert(ratio >= 0.0);
    assert(ratio <= 1.0);

    activitySpeedRatio = ratio;
}



bool ItemStorage::acceptItem(const ItemInformation* itemType) const
{
    // TODO: Take activity into account.
    // TODO: Take current stock into account.

    return availableItems.contains(itemType);
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
