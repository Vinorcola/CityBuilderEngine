#include "DeliveryCharacter.hpp"

#include <cassert>

#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"



DeliveryCharacter::DeliveryCharacter(
    QObject* parent,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    ProcessableBuilding& target,
    owner<PathInterface*> path,
    const ItemInformation& transportedItemConf,
    const int quantity
) :
    Character(parent, conf, issuer),
    pathGenerator(pathGenerator),
    target(&target),
    transportedItemConf(transportedItemConf),
    transportedQuantity(quantity),
    goingHome(false)
{
    motionHandler.takePath(path);
}



const ItemInformation& DeliveryCharacter::getTransportedItemConf() const
{
    return transportedItemConf;
}



bool DeliveryCharacter::isEmpty() const
{
    return transportedQuantity == 0;
}



int DeliveryCharacter::getTransportedQuantity() const
{
    return transportedQuantity;
}



void DeliveryCharacter::unload(const int quantity)
{
    assert(quantity <= transportedQuantity);

    transportedQuantity -= quantity;
}



void DeliveryCharacter::goHome()
{
    if (issuer) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestPathTo(
            motionHandler.getCurrentLocation(),
            issuer->getEntryPoint()
        ));
    }
}



void DeliveryCharacter::process(const CycleDate& date)
{
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
