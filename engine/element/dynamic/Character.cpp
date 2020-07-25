#include "Character.hpp"

#include "engine/element/dynamic/MotionHandler.hpp"
#include "global/conf/CharacterInformation.hpp"



Character::Character(QObject* parent,
    const Map* map,
    const CharacterInformation* conf,
    ProcessableBuilding* issuer,
    int wanderingCredits,
    owner<CarriedItem*> carriedItem
) :
    QObject(parent),
    AbstractProcessable(),
    conf(conf),
    issuer(issuer),
    target(),
    motionHandler(new MotionHandler(this, map, conf->getSpeed(), issuer->getEntryPoint(), wanderingCredits)),
    carriedItem(carriedItem)
{
    connect(motionHandler, &MotionHandler::wanderingCreditsExpired, [this]() {
        target = this->issuer;
        motionHandler->setTarget(this->issuer->getEntryPoint());
    });
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
    motionHandler->setTarget(target->getEntryPoint());
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



const CharacterInformation* Character::getConf() const
{
    return conf;
}



const MapCoordinates& Character::getCurrentLocation() const
{
    return motionHandler->getCurrentLocation();
}



ProcessableBuilding* Character::getIssuer() const
{
    return issuer;
}



void Character::process(const CycleDate& date)
{
    motionHandler->move();

    if (motionHandler->hasReachedTarget()) {
        motionHandler->resetTarget();
        if (target) {
            target->processInteraction(date, this);
        }
    }
}
