#include "Character.hpp"

#include "engine/element/dynamic/MotionHandler.hpp"
#include "global/conf/DynamicElementInformation.hpp"



Character::Character(
    QObject* parent,
    const Map* map,
    const DynamicElementInformation* conf,
    AbstractProcessableStaticMapElement* issuer,
    int randomWalkingCredit
) :
    QObject(parent),
    AbstractProcessable(),
    conf(conf),
    issuer(issuer),
    target(),
    motionHandler(new MotionHandler(this, map, conf->getSpeed(), issuer->getEntryPoint(), randomWalkingCredit))
{
    connect(motionHandler, &MotionHandler::wanderingCreditsExpired, [this]() {
        target = this->issuer;
        motionHandler->setTarget(this->issuer->getEntryPoint());
    });
}



void Character::assignTarget(AbstractProcessableStaticMapElement* target)
{
    this->target = target;
    motionHandler->setTarget(target->getEntryPoint());
}



const DynamicElementInformation* Character::getConf() const
{
    return conf;
}



const MapCoordinates& Character::getCurrentLocation() const
{
    return motionHandler->getCurrentLocation();
}



AbstractProcessableStaticMapElement* Character::getIssuer() const
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
