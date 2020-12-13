#include "DeliveryManCharacter.hpp"

#include <cassert>

#include "src/engine/map/dynamicElement/CharacterManagerInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/map/staticElement/building/BuildingSearchEngine.hpp"
#include "src/engine/map/staticElement/building/StorageBuilding.hpp"



DeliveryManCharacter::DeliveryManCharacter(
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const BuildingSearchEngine& searchEngine,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer,
    const ItemInformation& transportedItemConf,
    const int transportedQuantity
) :
    Character(characterManager, pathGenerator, conf, issuer),
    searchEngine(searchEngine),
    target(),
    transportedItemConf(transportedItemConf),
    transportedQuantity(transportedQuantity),
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
    auto issuer(this->issuer.toStrongRef());
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
        auto storage(searchEngine.findClosestStorageThatCanStore(transportedItemConf, motionHandler.getCurrentLocation()));
        if (storage) {
            target = storage;
            motionHandler.takePath(pathGenerator.generateShortestRoadPathTo(motionHandler.getCurrentLocation(), storage->getEntryPoint()));
        }
    }

    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (goingHome) {
            auto issuer(this->issuer.toStrongRef());
            if (issuer) {
                issuer->processInteraction(date, *this);
            }
            if (transportedQuantity == 0) {
                characterManager.clearCharacter(*this);
            }
            else {
                // TODO: Fetch a new target?
            }
        }
        else {
            auto target(this->target.toStrongRef());
            if (target) {
                target->processInteraction(date, *this);
                notifyViewDataChange();
                if (isEmpty()) {
                    goHome();
                }
                else {
                    // TODO: Fetch a new target?
                }
            }
        }
    }
}
