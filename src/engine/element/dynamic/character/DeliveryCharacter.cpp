#include "DeliveryCharacter.hpp"

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
    quantity(quantity),
    goingHome(false)
{
    motionHandler.takePath(path);
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
            }
        }
    }
}
