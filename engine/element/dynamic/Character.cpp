#include "Character.hpp"

#include "engine/element/dynamic/Character.hpp"
#include "global/conf/DynamicElementInformation.hpp"



Character::Character(QObject* parent, const DynamicElementInformation* conf, AbstractProcessableStaticMapElement* issuer) :
    AbstractProcessable(parent),
    conf(conf),
    initialLocation(issuer->getEntryPoint()),
    moveFromLocation(initialLocation),
    currentLocation(initialLocation),
    moveToLocation(initialLocation),
    issuer(issuer)
{

}



const DynamicElementInformation* Character::getConf() const
{
    return conf;
}



const MapCoordinates& Character::getInitialLocation() const
{
    return initialLocation;
}



const MapCoordinates& Character::getComingFromLocation() const
{
    return moveFromLocation;
}



const MapCoordinates& Character::getCurrentLocation() const
{
    return currentLocation;
}



const MapCoordinates& Character::getGoingToLocation() const
{
    return moveToLocation;
}



AbstractProcessableStaticMapElement* Character::getIssuer() const
{
    return issuer;
}



void Character::process(const CycleDate& date)
{
    if (moveToLocation.isValid()) {
        if (moveToLocation == currentLocation) {
            moveToLocation = findNextGoingToLocation(date);
            moveFromLocation = currentLocation;
            if (!moveToLocation.isValid()) {
                return;
            }
        }

        moveToTarget();
    }
}



void Character::moveToTarget()
{
    if (moveToLocation.getX() > currentLocation.getX()) {
        currentLocation.setX(qMin(currentLocation.getX() + conf->getSpeed(), moveToLocation.getX()));
    } else if (moveToLocation.getX() < currentLocation.getX()) {
        currentLocation.setX(qMax(currentLocation.getX() - conf->getSpeed(), moveToLocation.getX()));
    }
    if (moveToLocation.getY() > currentLocation.getY()) {
        currentLocation.setY(qMin(currentLocation.getY() + conf->getSpeed(), moveToLocation.getY()));
    } else if (moveToLocation.getY() < currentLocation.getY()) {
        currentLocation.setY(qMax(currentLocation.getY() - conf->getSpeed(), moveToLocation.getY()));
    }
}
