#include "Character.hpp"

#include "src/engine/element/dynamic/MotionHandler.hpp"
#include "src/global/conf/CharacterInformation.hpp"



Character::Character(
    QObject* parent,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding* issuer,
    int wanderingCredits,
    owner<CarriedItem*> carriedItem
) :
    QObject(parent),
    AbstractProcessable(),
    conf(conf),
    issuer(issuer),
    target(),
    motionHandler(pathGenerator, conf.getSpeed(), issuer->getEntryPoint(), wanderingCredits),
    carriedItem(carriedItem)
{

}



Character::~Character()
{
    if (carriedItem) {
        delete carriedItem;
    }
}



void Character::assignTarget(ProcessableBuilding* target)
{
    this->target = target;
    motionHandler.changeDestination(target->getEntryPoint());
}



owner<Character::CarriedItem*> Character::takeCarriedItems(const int maxQuantity)
{
    if (carriedItem->quantity <= maxQuantity) {
        auto items(carriedItem);
        carriedItem = nullptr;

        return items;
    } else {
        carriedItem->quantity -= maxQuantity;

        return new CarriedItem(carriedItem->conf, maxQuantity);
    }
}



const CharacterInformation& Character::getConf() const
{
    return conf;
}



const MapCoordinates& Character::getCurrentLocation() const
{
    return motionHandler.getCurrentLocation();
}



ProcessableBuilding* Character::getIssuer() const
{
    return issuer;
}



void Character::process(const CycleDate& date)
{
    motionHandler.move();

    if (motionHandler.isPathCompleted()) {
        if (target) {
            motionHandler.resetDestination();
            target->processInteraction(date, this);
        }
        else {
            assignTarget(issuer);
        }
    }
}
