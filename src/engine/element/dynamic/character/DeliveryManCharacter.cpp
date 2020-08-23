#include "DeliveryManCharacter.hpp"

#include <cassert>

#include "src/engine/element/static/building/StorageBuilding.hpp"
#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/MapSearchEngine.hpp"



DeliveryManCharacter::DeliveryManCharacter(
    QObject* parent,
    const MapSearchEngine& searchEngine,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    const ItemInformation& transportedItemConf,
    const int quantity
) :
    Character(parent, conf, issuer),
    searchEngine(searchEngine),
    pathGenerator(pathGenerator),
    target(),
    transportedItemConf(transportedItemConf),
    transportedQuantity(quantity),
    goingHome(false)
{

}



const ItemInformation& DeliveryManCharacter::getTransportedItemConf() const
{
    return transportedItemConf;
}



bool DeliveryManCharacter::isEmpty() const
{
    return transportedQuantity == 0;
}



int DeliveryManCharacter::getTransportedQuantity() const
{
    return transportedQuantity;
}



void DeliveryManCharacter::unload(const int quantity)
{
    assert(quantity <= transportedQuantity);

    transportedQuantity -= quantity;
}



void DeliveryManCharacter::goHome()
{
    if (issuer) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestRoadPathTo(
            motionHandler.getCurrentLocation(),
            issuer->getEntryPoint()
        ));
    }
}



void DeliveryManCharacter::process(const CycleDate& date)
{
    if (target.isNull()) {
        target = searchEngine.getStorageThatCanStore(transportedItemConf);
        if (target) {
            motionHandler.takePath(pathGenerator.generateShortestRoadPathTo(motionHandler.getCurrentLocation(), target->getEntryPoint()));
        }
    }

    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (goingHome) {
            if (issuer) {
                issuer->processInteraction(date, *this);
            }
        }
        else {
            if (target) {
                target->processInteraction(date, *this);
                if (isEmpty()) {
                    goHome();
                }
                else{
                    // TODO: Fetch a new target?
                }
            }
        }
    }
}
