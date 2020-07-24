#include "Character.hpp"

#include "engine/element/dynamic/MotionHandler.hpp"
#include "global/conf/CharacterInformation.hpp"



Character::Character(QObject* parent,
    const Map* map,
    const CharacterInformation* conf,
    AbstractProcessableStaticMapElement* issuer,
    int wanderingCredits
) :
    QObject(parent),
    AbstractProcessable(),
    conf(conf),
    issuer(issuer),
    target(),
    motionHandler(new MotionHandler(this, map, conf->getSpeed(), issuer->getEntryPoint(), wanderingCredits))
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



const CharacterInformation* Character::getConf() const
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
